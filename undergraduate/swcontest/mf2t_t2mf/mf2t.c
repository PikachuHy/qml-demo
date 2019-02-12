/* $Id: mf2t.c,v 1.5 1995/12/14 20:20:10 piet Rel $ */
/*
 * mf2t
 * 
 * Convert a MIDI file to text.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "midifile.h"
#include "version.h"

static int TrkNr;
static int TrksToDo = 1;
static int Measure, M0, Beat, Clicks;
static long T0;

/* options */

static int fold = 0;		/* fold long lines */
static int notes = 0;		/* print notes as a–g */
static int times = 0;		/* print times as Measure/beat/click */

static char *Onmsg  = "On ch=%d n=%s v=%d\n";
static char *Offmsg = "Off ch=%d n=%s v=%d\n";
static char *PoPrmsg = "PoPr ch=%d n=%s v=%d\n";
static char *Parmsg = "Par ch=%d c=%d v=%d\n";
static char *Pbmsg  = "Pb ch=%d v=%d\n";
static char *PrChmsg = "PrCh ch=%d p=%d\n";
static char *ChPrmsg = "ChPr ch=%d v=%d\n";

static void error(char *s)
{
    if (TrksToDo <= 0)
        fprintf(stderr, "Error: Garbage at end\n");
    else
        fprintf(stderr, "Error: %s\n", s);
}

static void prtime(void)
{
    if (times) {
        long m = (Mf_currtime-T0)/Beat;
        printf("%ld:%ld:%ld ",
                m/Measure+M0, m%Measure, (Mf_currtime-T0)%Beat);
    } else
        printf("%ld ",Mf_currtime);
}

static void prtext(unsigned char *p, int leng)
{
    int n, c;
    int pos = 25;

    printf("\"");
    for (n = 0; n < leng; n++) {
        c = *p++;
        if (fold && pos >= fold) {
            printf("\\\n\t");
            pos = 13;	/* tab + \xab + \ */
            if (c == ' ' || c == '\t') {
                putchar('\\');
                ++pos;
            }
        }
        switch (c) {
            case '\\':
            case '"':
                printf("\\%c", c);
                pos += 2;
                break;
            case '\r':
                printf("\\r");
                pos += 2;
                break;
            case '\n':
                printf("\\n");
                pos += 2;
                break;
            case '\0':
                printf("\\0");
                pos += 2;
                break;
            default:
                if (c >= 0x20) {
                    putchar(c);
                    ++pos;
                } else {
                    printf("\\x%02x" , c);
                    pos += 4;
                }
        }
    }
    printf("\"\n");
}

static void prhex(unsigned char *p,  int leng)
{
    int n;
    int pos = 25;

    for (n = 0; n < leng; n++, p++) {
        if (fold && pos >= fold) {
            printf("\\\n\t%02x", *p);
            pos = 14;	/* tab + ab + " ab" + \ */
        } else {
            printf(" %02x" , *p);
            pos += 3;
        }
    }
    printf("\n");
}

static char *mknote(int pitch)
{
    static char *Notes[] =
        { "c", "c#", "d", "d#", "e", "f", "f#", "g",
          "g#", "a", "a#", "b" };
    static char buf[5];
    if (notes)
        sprintf(buf, "%s%d", Notes[pitch % 12], pitch/12);
    else
        sprintf(buf, "%d", pitch);
    return buf;
}

static void myheader(int format, int ntrks, int division)
{
    if (division & 0x8000) { /* SMPTE */
        times = 0; /* Can’t do beats */
        printf("MFile %d %d %d %d\n",format,ntrks,
                -((-(division>>8))&0xff), division&0xff);
    } else
        printf("MFile %d %d %d\n",format,ntrks,division);
    if (format > 2) {
        fprintf(stderr, "Can’t deal with format %d files\n", format);
        exit (1);
    }
    Beat = Clicks = division;
    TrksToDo = ntrks;
}

static void mytrstart(void)
{
    printf("MTrk\n");
    TrkNr ++;
}

static void mytrend(void)
{
    printf("TrkEnd\n");
    --TrksToDo;
}

static void mynon(int chan, int pitch, int vol)
{
    prtime();
    printf(Onmsg, chan+1, mknote(pitch), vol);
}

static void mynoff(int chan, int pitch, int vol)
{
    prtime();
    printf(Offmsg, chan+1, mknote(pitch), vol);
}

static void mypressure(int chan, int pitch, int press)
{
    prtime();
    printf(PoPrmsg, chan+1, mknote(pitch), press);
}

static void myparameter(int chan, int control, int value)
{
    prtime();
    printf(Parmsg, chan+1, control, value);
}

static void mypitchbend(int chan, int lsb, int msb)
{
    prtime();
    printf(Pbmsg, chan+1, 128*msb+lsb);
}

static void myprogram(int chan, int program)
{
    prtime();
    printf(PrChmsg, chan+1, program);
}

static void mychanpressure(int chan, int press)
{
    prtime();
    printf(ChPrmsg, chan+1, press);
}

static void mysysex(int leng, char *mess)
{
    prtime();
    printf("SysEx");
    prhex((unsigned char *)mess, leng);
}

static void mymmisc(int type, int leng, char *mess)
{
    prtime();
    printf("Meta 0x%02x",type);
    prhex((unsigned char *)mess, leng);
}

static void mymspecial(int leng, char *mess)
{
    prtime();
    printf("SeqSpec");
    prhex((unsigned char *)mess, leng);
}

static void mymtext(int type, int leng, char *mess)
{
    static char *ttype[] = {
        NULL,
        "Text",         /* type=0x01 */
        "Copyright",    /* type=0x02 */
        "TrkName",
        "InstrName",    /* ...       */
        "Lyric",
        "Marker",
        "Cue",          /* type=0x07 */
        "Unrec"
    };
    int unrecognized = (sizeof(ttype)/sizeof(char *)) - 1;

    prtime();
    if (type < 1 || type > unrecognized)
        printf("Meta 0x%02x ",type);
    else if (type == 3 && TrkNr == 1)
        printf("Meta SeqName ");
    else
        printf("Meta %s ",ttype[type]);
    prtext((unsigned char *)mess, leng);
}

static void mymseq(int num)
{
    prtime();
    printf("SeqNr %d\n",num);
}

static void mymeot(void)
{
    prtime();
    printf("Meta TrkEnd\n");
}

static void mykeysig(int sf, int mi)
{
    prtime();
    printf("KeySig %d %s\n", (sf>127?sf-256:sf), (mi?"minor":"major"));
}

static void mytempo(long tempo)
{
    prtime();
    printf("Tempo %ld\n",tempo);
}

static void mytimesig(int nn, int dd, int cc, int bb)
{
    int denom = 1;
    while (dd-- > 0)
        denom *= 2;
    prtime();
    printf("TimeSig %d/%d %d %d\n", nn,denom,cc,bb);
    M0 += (Mf_currtime-T0)/(Beat*Measure);
    T0 = Mf_currtime;
    Measure = nn;
    Beat = 4 * Clicks / denom;
}

static void mysmpte(int hr, int mn, int se, int fr, int ff)
{
    prtime();
    printf("SMPTE %d %d %d %d %d\n", hr, mn, se, fr, ff);
}

static void myarbitrary(int leng, char *mess)
{
    prtime();
    printf("Arb");
    prhex ((unsigned char *)mess, leng);
}

static void initfuncs(void)
{
    Mf_error = error;
    Mf_getc = getchar;
    Mf_header =  myheader;
    Mf_starttrack =  mytrstart;
    Mf_endtrack =  mytrend;
    Mf_on =  mynon;
    Mf_off =  mynoff;
    Mf_pressure =  mypressure;
    Mf_parameter =  myparameter;
    Mf_pitchbend =  mypitchbend;
    Mf_program =  myprogram;
    Mf_chanpressure =  mychanpressure;
    Mf_sysex =  mysysex;
    Mf_metamisc =  mymmisc;
    Mf_seqnum =  mymseq;
    Mf_eot =  mymeot;
    Mf_timesig =  mytimesig;
    Mf_smpte =  mysmpte;
    Mf_tempo =  mytempo;
    Mf_keysig =  mykeysig;
    Mf_sqspecific =  mymspecial;
    Mf_text =  mymtext;
    Mf_arbitrary =  myarbitrary;
}

static void usage(void)
{
    fprintf(stderr,
"mf2t v%s\n"
"Usage: mf2t [-mnbtv] [-f n] [midifile [textfile]]\n\n"
"Options:\n"
"  -m      merge partial sysex into a single sysex message\n"
"  -n      write notes in symbolic form\n"
"  -b|-t   write event times as bar:beat:click\n"
"  -v      use slightly more verbose output\n"
"  -f n    fold long text and hex entries at n characters\n", VERSION);
    exit(1);
}

int main(int argc, char **argv)
{
    int c;

    Mf_nomerge = 1;
    while ((c = getopt(argc, argv, "mnbtvf:h")) != -1) {
        switch (c) {
            case 'm':
                Mf_nomerge = 0;
                break;
            case 'n':
                notes++;
                break;
            case 'b':
            case 't':
                times++;
                break;
            case 'v':
                Onmsg  = "On ch=%d note=%s vol=%d\n";
                Offmsg = "Off ch=%d note=%s vol=%d\n";
                PoPrmsg = "PolyPr ch=%d note=%s val=%d\n";
                Parmsg = "Param ch=%d con=%d val=%d\n";
                Pbmsg  = "Pb ch=%d val=%d\n";
                PrChmsg = "ProgCh ch=%d prog=%d\n";
                ChPrmsg = "ChanPr ch=%d val=%d\n";
                break;
            case 'f':
                fold = atoi(optarg);
                break;
            case 'h':
            case '?':
            default:
                usage();
        }
    }

    if (optind < argc && !freopen(argv[optind++], "r", stdin)) {
        fprintf(stderr, "freopen (%s): %s\n", argv[optind - 1],
                strerror(errno));
        exit(1);
    }

    if (optind < argc && !freopen(argv[optind], "w", stdout)) {
        fprintf(stderr, "freopen (%s): %s\n", argv[optind],
                strerror(errno));
        exit(1);
    }

    initfuncs();
    TrkNr = 0;
    Measure = 4;
    Beat = 96;
    Clicks = 96;
    T0 = 0;
    M0 = 0;
    mfread();

    return 0;
}
