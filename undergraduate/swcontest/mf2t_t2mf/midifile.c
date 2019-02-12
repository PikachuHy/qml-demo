/* $Id: midifile.c,v 1.4 1991/11/17 21:57:26 piet Rel piet $ */
/*
 * midifile 1.11
 * 
 * Read and write a MIDI file.  Externally‐assigned function pointers are 
 * called upon recognizing things in the file.
 *
 * Original release by Tim Thompson, tjt@twitch.att.com
 *
 * June 1989 – Added writing capability, M. Czeiszperger.
 *
 * Oct 1991 – Modifications by Piet van Oostrum <piet@cs.ruu.nl>:
 *      Changed identifiers to be 7 char unique.
 *      Added sysex write capability (mf_w_sysex_event)
 *      Corrected a bug in writing of tempo track
 *      Added code to implement running status on write
 *      Added check for meta end of track insertion
 *      Added a couple of include files to get proper int=short compilation
 *
 * Nov 1991 – Piet van Oostrum <piet@cs.ruu.nl>
 *      mf_w_tempo needs a delta time parameter otherwise the tempo cannot
 *      be changed during the piece.
 *
 * Apr 1993 – Piet van Oostrum <piet@cs.ruu.nl>
 *      decl of malloc replaced by #include <malloc.h>
 *      readheader() declared void.
 *
 * Aug 1993 – Piet van Oostrum <piet@cs.ruu.nl>
 *      sequencer_specific in midifile.h was wrong
 *
 *          The file format implemented here is called
 *          Standard MIDI Files, and is part of the Musical
 *          instrument Digital Interface specification.
 *          The spec is avaiable from:
 *
 *               International MIDI Association
 *               5316 West 57th Street
 *               Los Angeles, CA 90056
 *
 *          An in‐depth description of the spec can also be found
 *          in the article “Introducing Standard MIDI Files”, published
 *          in Electronic Musician magazine, April, 1989.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "midifile.h"

//#include "windows.h"

#define NULLFUNC 0

/* public stuff */

/* Functions to be called while processing the MIDI file. */
MIDIFILE_PUBLIC int (*Mf_getc)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_error)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_header)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_starttrack)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_endtrack)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_on)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_off)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_pressure)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_parameter)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_pitchbend)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_program)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_chanpressure)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_sysex)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_arbitrary)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_metamisc)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_seqnum)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_eot)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_smpte)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_tempo)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_timesig)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_keysig)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_sqspecific)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_text)() = NULLFUNC;

/* Functions to implement in order to write a MIDI file */
MIDIFILE_PUBLIC int (*Mf_putc)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_wtrack)() = NULLFUNC;
MIDIFILE_PUBLIC void (*Mf_wtempotrack)() = NULLFUNC;

/* 1 => continued system exclusives are not collapsed */
MIDIFILE_PUBLIC int Mf_nomerge = 0;
/* current time in delta‐time units */
MIDIFILE_PUBLIC long Mf_currtime = 0L;

/* private stuff */
static long Mf_toberead = 0L;
static long Mf_numbyteswritten = 0L;

static void mferror(char *s)
{
    if (Mf_error)
        (*Mf_error)(s);
    exit(1);
}

static void badbyte(int c)
{
    char buff[32];

    (void) sprintf(buff,"unexpected byte: 0x%02x",c);
    mferror(buff);
}

static int egetc(void) /* read a single character and abort on EOF */
{
	
    int c = (*Mf_getc)();

	//if (feof(stdin))
	//OutputDebugStringA("%d",i++);
	

//    if (c == EOF)
	if (feof(stdin))
        mferror("premature EOF");
 
	
	Mf_toberead--;
    return(c);
}

/* readvarinum – read a varying‐length number, and return the */
/* number of characters it took. */

static long readvarinum(void)
{
    long value;
    int c;

    c = egetc();
    value = c;
    if (c & 0x80) {
        value &= 0x7f;
        do {
            c = egetc();
            value = (value << 7) + (c & 0x7f);
        } while (c & 0x80);
    }
    return(value);
}

static long to32bit(int c1, int c2, int c3, int c4)
{
    long value = 0L;

    value = (c1 & 0xff);
    value = (value<<8) + (c2 & 0xff);
    value = (value<<8) + (c3 & 0xff);
    value = (value<<8) + (c4 & 0xff);
    return (value);
}

static int to16bit(int c1, int c2)
{
    return ((c1 & 0xff ) << 8) + (c2 & 0xff);
}

static long read32bit(void)
{
    int c1, c2, c3, c4;

    c1 = egetc();
    c2 = egetc();
    c3 = egetc();
    c4 = egetc();
    return to32bit(c1, c2, c3, c4);
}

static int read16bit(void)
{
    int c1, c2;
    c1 = egetc();
    c2 = egetc();
    return to16bit(c1, c2);
}

/* 
 * This routine converts delta times in ticks into seconds. The
 * else statement is needed because the formula is different for tracks
 * based on notes and tracks based on SMPTE times.
 *
 */
MIDIFILE_PUBLIC float mf_ticks2sec(unsigned long ticks, int division,
        unsigned int tempo)
{
    float smpte_format, smpte_resolution;

    if (division > 0)
        return ((float) (((float)(ticks) * (float)(tempo)) /
                ((float)(division) * 1000000.0)));
    else {
        smpte_format = upperbyte(division);
        smpte_resolution = lowerbyte(division);
        return (float) ((float) ticks / (smpte_format * smpte_resolution *
                1000000.0));
    }
} /* end of ticks2sec() */

MIDIFILE_PUBLIC unsigned long mf_sec2ticks(float secs, int division,
        unsigned int tempo)
{    
     return (long)(((secs * 1000.0) / 4.0 * division) / tempo);
}

/* The code below allows collection of a system exclusive message of */
/* arbitrary length.  The Msgbuff is expanded as necessary.  The only */
/* visible data/routines are msginit(), msgadd(), msg(), msgleng(). */

#define MSGINCREMENT 128
static char *Msgbuff = NULL;  /* message buffer */
static int Msgsize = 0;       /* Size of currently allocated Msg */
static int Msgindex = 0;      /* index of next available location in Msg */

static void msginit(void)
{
    Msgindex = 0;
}

static char *msg(void)
{
    return(Msgbuff);
}

static int msgleng(void)
{
    return(Msgindex);
}

static void biggermsg(void)
{
    char *newmess;
    char *oldmess = Msgbuff;
    int oldleng = Msgsize;

    Msgsize += MSGINCREMENT;
    newmess = (char *)malloc((unsigned)(sizeof(char)*Msgsize));

    if (newmess == NULL)
        mferror("malloc error!");

    /* copy old message into larger new one */
    if (oldmess != NULL) {
        register char *p = newmess;
        register char *q = oldmess;
        register char *endq = &oldmess[oldleng];

        for (; q!=endq; p++, q++)
            *p = *q;
        free(oldmess);
    }
    Msgbuff = newmess;
}

static void msgadd(int c)
{
    /* If necessary, allocate larger message buffer. */
    if (Msgindex >= Msgsize)
        biggermsg();
    Msgbuff[Msgindex++] = c;
}

static void metaevent(int type)
{
    int leng = msgleng();
    char *m = msg();

    switch (type) {
        case 0x00:
            if (Mf_seqnum)
            (*Mf_seqnum)(to16bit(m[0],m[1]));
            break;
        case 0x01:      /* Text event */
        case 0x02:      /* Copyright notice */
        case 0x03:      /* Sequence/Track name */
        case 0x04:      /* Instrument name */
        case 0x05:      /* Lyric */
        case 0x06:      /* Marker */
        case 0x07:      /* Cue point */
        case 0x08:
        case 0x09:
        case 0x0a:
        case 0x0b:
        case 0x0c:
        case 0x0d:
        case 0x0e:
        case 0x0f:
            /* These are all text events */
            if (Mf_text)
                (*Mf_text)(type,leng,m);
            break;
        case 0x2f:      /* End of Track */
            if (Mf_eot)
                (*Mf_eot)();
            break;
        case 0x51:      /* Set tempo */
            if (Mf_tempo)
                (*Mf_tempo)(to32bit(0,m[0],m[1],m[2]));
            break;
        case 0x54:
            if (Mf_smpte)
                (*Mf_smpte)(m[0],m[1],m[2],m[3],m[4]);
            break;
        case 0x58:
            if (Mf_timesig)
                (*Mf_timesig)(m[0],m[1],m[2],m[3]);
            break;
        case 0x59:
            if (Mf_keysig)
                (*Mf_keysig)(m[0],m[1]);
            break;
        case 0x7f:
            if (Mf_sqspecific)
                (*Mf_sqspecific)(leng,m);
            break;
        default:
            if (Mf_metamisc)
                (*Mf_metamisc)(type,leng,m);
    }
}

static void sysex(void)
{
    if (Mf_sysex)
        (*Mf_sysex)(msgleng(),msg());
}

static void chanmessage(int status, int c1, int c2)
{
    int chan = status & 0xf;

    switch ( status & 0xf0 ) {
        case 0x80:
            if (Mf_off)
                (*Mf_off)(chan, c1, c2);
            break;
        case 0x90:
            if (Mf_on)
                (*Mf_on)(chan, c1, c2);
            break;
        case 0xa0:
            if (Mf_pressure)
                (*Mf_pressure)(chan, c1, c2);
            break;
        case 0xb0:
            if (Mf_parameter)
                (*Mf_parameter)(chan, c1, c2);
            break;
        case 0xe0:
            if (Mf_pitchbend)
                (*Mf_pitchbend)(chan, c1, c2);
            break;
        case 0xc0:
            if (Mf_program)
                (*Mf_program)(chan, c1);
            break;
        case 0xd0:
            if (Mf_chanpressure)
                (*Mf_chanpressure)(chan, c1);
            break;
    }
}

static int readmt(char *s) /* read through the “MThd” or “MTrk” header string */
{
    int n = 0;
    char *p = s;
    int c;

    while (n++<4 && (c=(*Mf_getc)()) != EOF) {
        if (c != *p++) {
            char buff[32];
            (void) strcpy(buff,"expecting ");
            (void) strcat(buff,s);
            mferror(buff);
        }
    }
    return(c);
}

static void readheader(void) /* read a header chunk */
{
    int format, ntrks, division;

    if (readmt("MThd") == EOF)
        return;

    Mf_toberead = read32bit();
    format = read16bit();
    ntrks = read16bit();
    division = read16bit();

    if (Mf_header)
        (*Mf_header)(format,ntrks,division);

    /* flush any extra stuff, in case the length of header is not 6 */
    while (Mf_toberead > 0)
        (void) egetc();
}

static int readtrack(void) /* read a track chunk */
{
    /* This array is indexed by the high half of a status byte.  It’s */
    /* value is either the number of bytes needed (1 or 2) for a channel */
    /* message, or 0 (meaning it’s not  a channel message). */
    static int chantype[] = {
        0, 0, 0, 0, 0, 0, 0, 0,    /* 0x00 through 0x70 */
        2, 2, 2, 2, 1, 1, 2, 0     /* 0x80 through 0xf0 */
    };
    long varinum, lookfor;
    int c, c1 = 0, type;
    int sysexcontinue = 0; /* 1 if last message was an unfinished sysex */
    int running = 0;       /* 1 when running status used */
    int status = 0;        /* status value (e.g. 0x90==note‐on) */
    int needed;

    if (readmt("MTrk") == EOF)
        return(0);

    Mf_toberead = read32bit();
    Mf_currtime = 0;

    if (Mf_starttrack)
        (*Mf_starttrack)();

    while (Mf_toberead > 0) {
        Mf_currtime += readvarinum();    /* delta time */

        c = egetc();

        if (sysexcontinue && c != 0xf7)
            mferror("didn’t find expected continuation of a sysex");

        if ((c & 0x80) == 0) {   /* running status? */
            if (status == 0)
                mferror("unexpected running status");
            running = 1;
            c1 = c;
            c = status;
        } else if (c < 0xf0) {
            status = c;
            running = 0;
        }

        needed = chantype[(c>>4) & 0xf];

        if (needed) { /* ie. is it a channel message? */
            if (! running)
                c1 = egetc();
            chanmessage(status, c1, (needed>1) ? egetc() : 0);
            continue;;
        }

        switch (c) {
            case 0xff:     /* meta event */
                type = egetc();
                /*
                 * This doesn’t work with GCC
                 * lookfor = Mf_toberead - readvarinum();
                 */
                varinum = readvarinum();
                lookfor = Mf_toberead - varinum;
                msginit();

                while (Mf_toberead > lookfor)
                    msgadd(egetc());

                metaevent(type);
                break;

            case 0xf0:     /* start of system exclusive */
                /*
                 * This doesn’t work with GCC
                 * lookfor = Mf_toberead - readvarinum();
                 */
                varinum = readvarinum();
                lookfor = Mf_toberead - varinum;
                msginit();
                msgadd(0xf0);

                while (Mf_toberead > lookfor)
                    msgadd(c = egetc());

                if (c == 0xf7 || Mf_nomerge == 0)
                    sysex();
                else
                    sysexcontinue = 1;  /* merge into next msg */
                break;

            case 0xf7:     /* sysex continuation or arbitrary stuff */
                /*
                 * This doesn’t work with GCC
                 * lookfor = Mf_toberead - readvarinum();
                 */
                varinum = readvarinum();
                lookfor = Mf_toberead - varinum;

                if (! sysexcontinue)
                    msginit();

                while (Mf_toberead > lookfor)
                    msgadd(c=egetc());

                if ( ! sysexcontinue ) {
                    if (Mf_arbitrary)
                        (*Mf_arbitrary)(msgleng(),msg());
                } else if (c == 0xf7) {
                    sysex();
                    sysexcontinue = 0;
                }
                break;
            default:
                badbyte(c);
                break;
        }
    }

    if (Mf_endtrack)
        (*Mf_endtrack)();
    return(1);
}

MIDIFILE_PUBLIC void mfread(void)
{
    if ( Mf_getc == NULLFUNC )
        mferror("mfread() called without setting Mf_getc"); 

    readheader();
    while (readtrack());
}

/* for backward compatibility with the original lib */
MIDIFILE_PUBLIC void midifile(void)
{
    mfread();
}

/* write a single character and abort on error */
static int eputc(unsigned char c)
{
    int return_val;

    if ((Mf_putc) == NULLFUNC) {
        mferror("Mf_putc undefined");
        return(-1);
    }

    return_val = (*Mf_putc)(c);

    if (return_val == EOF)
        mferror("error writing");

    Mf_numbyteswritten++;
    return(return_val);
}

/*
 * write32bit()
 * write16bit()
 *
 * These routines are used to make sure that the byte order of
 * the various data types remains constant between machines. This
 * helps make sure that the code will be portable from one system
 * to the next.  It is slightly dangerous that it assumes that longs
 * have at least 32 bits and ints have at least 16 bits, but this
 * has been true at least on PCs, UNIX machines, and Macintosh’s.
 *
 */
static void write32bit(unsigned long data)
{
    eputc((unsigned)((data >> 24) & 0xff));
    eputc((unsigned)((data >> 16) & 0xff));
    eputc((unsigned)((data >> 8 ) & 0xff));
    eputc((unsigned)(data & 0xff));
}

static void write16bit(int data)
{
    eputc((unsigned)((data & 0xff00) >> 8));
    eputc((unsigned)(data & 0xff));
}

static void WriteVarLen(unsigned long value)
{
    unsigned long buffer;

    buffer = value & 0x7f;
    while ((value >>= 7) > 0) {
        buffer <<= 8;
        buffer |= 0x80;
        buffer += (value & 0x7f);
    }
    while (1) {
        eputc((unsigned)(buffer & 0xff));
       
        if (buffer & 0x80)
            buffer >>= 8;
        else
            return;
    }
}/* end of WriteVarLen */

static void mf_w_header_chunk(int format, int ntracks, int division)
{
    unsigned long ident,length;
    void write16bit(),write32bit();
    
    ident = MThd;           /* Head chunk identifier                    */
    length = 6;             /* Chunk length                             */

    /* individual bytes of the header must be written separately
       to preserve byte order across cpu types :-( */
    write32bit(ident);
    write32bit(length);
    write16bit(format);
    write16bit(ntracks);
    write16bit(division);
} /* end gen_header_chunk() */

MIDIFILE_PUBLIC int Mf_RunStat = 0;    /* if nonzero, use running status */
static int laststat;                   /* last status code */
static int lastmeta;                   /* last meta event type */

/*
 * mf_w_midi_event()
 * 
 * Library routine to mf_write a single MIDI track event in the standard MIDI
 * file format. The format is:
 *
 *                    <delta‐time><event>
 *
 * In this case, event can be any multi‐byte midi message, such as
 * “note on”, “note off”, etc.      
 *
 * delta_time – the time in ticks since the last event.
 * type – the type of event.
 * chan – The midi channel.
 * data – A pointer to a block of chars containing the META EVENT,
 *        data.
 * size – The length of the midi‐event data.
 */
MIDIFILE_PUBLIC int mf_w_midi_event(unsigned long delta_time,
        unsigned int type, unsigned int chan, unsigned char *data,
        unsigned long size)
{
    int i;
    unsigned char c;

    WriteVarLen(delta_time);

    /* all MIDI events start with the type in the first four bits,
       and the channel in the lower four bits */
    c = type | chan;

    if (chan > 15)
        perror("error: MIDI channel greater than 16\n");

    if (!Mf_RunStat || laststat != c)
        eputc(c);

    laststat = c;

    /* write out the data bytes */
    for (i = 0; i < size; i++)
        eputc(data[i]);

    return(size);
} /* end mf_write MIDI event */

/*
 * mf_w_meta_event()
 *
 * Library routine to mf_write a single meta event in the standard MIDI
 * file format. The format of a meta event is:
 *
 *          <delta‐time><FF><type><length><bytes>
 *
 * delta_time – the time in ticks since the last event.
 * type – the type of meta event.
 * data – A pointer to a block of chars containing the META EVENT,
 *        data.
 * size – The length of the meta‐event data.
 */
MIDIFILE_PUBLIC int mf_w_meta_event(unsigned long delta_time,
        unsigned char type, unsigned char *data, unsigned long size)
{
    int i;

    WriteVarLen(delta_time);
    
    /* This marks the fact we’re writing a meta‐event */
    eputc(meta_event);
    laststat = meta_event;

    /* The type of meta event */
    eputc(type);
    lastmeta = type;

    /* The length of the data bytes to follow */
    WriteVarLen(size); 

    for (i = 0; i < size; i++) {
        if (eputc(data[i]) != data[i])
            return(-1); 
    }
    return(size);
} /* end mf_w_meta_event */

/*
 * mf_w_sysex_event()
 *
 * Library routine to mf_write a single sysex (or arbitrary)
 * event in the standard MIDI file format. The format of the event is:
 *
 *          <delta‐time><type><length><bytes>
 *
 * delta_time – the time in ticks since the last event.
 * data – A pointer to a block of chars containing the EVENT data.
 *        The first byte is the type (0xf0 for sysex, 0xf7 otherwise)
 * size – The length of the sysex‐event data.
 */
MIDIFILE_PUBLIC int mf_w_sysex_event(unsigned long delta_time,
        unsigned char *data, unsigned long size)
{
    int i;

    WriteVarLen(delta_time);
    
    /* The type of sysex event */
    eputc(*data);
    laststat = 0;

    /* The length of the data bytes to follow */
    WriteVarLen(size-1); 

    for (i = 1; i < size; i++) {
        if (eputc(data[i]) != data[i])
            return(-1); 
    }
    return(size);
} /* end mf_w_sysex_event */

MIDIFILE_PUBLIC void mf_w_tempo(unsigned long delta_time,
        unsigned long tempo)
{
    /* Write tempo */
    /* all tempos are written as 120 beats/minute, */
    /* expressed in microseconds/quarter note     */

    WriteVarLen(delta_time);

    eputc(meta_event);
    laststat = meta_event;
    eputc(set_tempo);

    eputc(3);
    eputc((unsigned)(0xff & (tempo >> 16)));
    eputc((unsigned)(0xff & (tempo >> 8)));
    eputc((unsigned)(0xff & tempo));
}

static void mf_w_track_chunk(int which_track, FILE *fp, void (*wtrack)())
{
    unsigned long trkhdr,trklength;
    long offset, place_marker;
    void write16bit(),write32bit();

    trkhdr = MTrk;
    trklength = 0;

    /* Remember where the length was written, because we don’t
       know how long it will be until we’ve finished writing */
    offset = ftell(fp); 

#ifdef DEBUG
    printf("offset = %d\n",(int) offset);
#endif

    /* Write the track chunk header */
    write32bit(trkhdr);
    write32bit(trklength);

    Mf_numbyteswritten = 0L; /* the header’s length doesn’t count */
    laststat = 0;

    /* Note: this calls Mf_writetempotrack with an unused parameter (-1)
       But this is innocent */

    (*wtrack)(which_track);

    if (laststat != meta_event || lastmeta != end_of_track) {
        /* mf_write End of track meta event */
        eputc(0);
        eputc(meta_event);
        eputc(end_of_track);
        eputc(0);
    }

    laststat = 0;
     
    /* It’s impossible to know how long the track chunk will be beforehand,
       so the position of the track length data is kept so that it can
       be written after the chunk has been generated */
    place_marker = ftell(fp);

    /* This method turned out not to be portable because the
       parameter returned from ftell is not guaranteed to be
       in bytes on every machine */
    /* track.length = place_marker - offset - (long) sizeof(track); */

#ifdef DEBUG
    printf("length = %d\n",(int) trklength);
#endif

    if (fseek(fp,offset,0) < 0)
        mferror("error seeking during final stage of write");

    trklength = Mf_numbyteswritten;

    /* Re‐mf_write the track chunk header with right length */
    write32bit(trkhdr);
    write32bit(trklength);

    fseek(fp,place_marker,0);
} /* End gen_track_chunk() */

/*
 * mfwrite() – The only function you’ll need to call to write out
 *             a midi file.
 *
 * format      0 – Single multi‐channel track
 *             1 – Multiple simultaneous tracks
 *             2 – One or more sequentially independent
 *                 single track patterns                
 * ntracks     The number of tracks in the file.
 * division    This is kind of tricky, it can represent two
 *             things, depending on whether it is positive or negative
 *             (bit 15 set or not).  If  bit  15  of division  is zero,
 *             bits 14 through 0 represent the number of delta‐time
 *             “ticks” which make up a quarter note.  If bit  15 of
 *             division  is  a one, delta‐times in a file correspond to
 *             subdivisions of a second similiar to  SMPTE  and  MIDI
 *             time code.  In  this format bits 14 through 8 contain
 *             one of four values – 24, -25, -29, or -30,
 *             corresponding  to  the  four standard  SMPTE and MIDI
 *             time code frame per second formats, where  -29
 *             represents  30  drop  frame.   The  second  byte
 *             consisting  of  bits 7 through 0 corresponds the the
 *             resolution within a frame.  Refer the Standard MIDI
 *             Files 1.0 spec for more details.
 * fp          This should be the open file pointer to the file you
 *             want to write.  It will have be a global in order
 *             to work with Mf_putc.  
 */ 

MIDIFILE_PUBLIC void mfwrite(int format, int ntracks, int division,
        FILE *fp)
{
    int i;

    if (Mf_putc == NULLFUNC)
        mferror("mfmf_write() called without setting Mf_putc");

    if (Mf_wtrack == NULLFUNC)
        mferror("mfmf_write() called without setting Mf_mf_writetrack"); 

    /* every MIDI file starts with a header */
    mf_w_header_chunk(format,ntracks,division);

    /* In format 1 files, the first track is a tempo map */
    if (format == 1 && ( Mf_wtempotrack )) {
        mf_w_track_chunk(-1, fp, Mf_wtempotrack);
        ntracks--;
    }

    /* The rest of the file is a series of tracks */
    for (i = 0; i < ntracks; i++)
        mf_w_track_chunk(i, fp, Mf_wtrack);
}
