#ifndef MIDIFILE_H
#define MIDIFILE_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined BUILDING_MIDIFILE && defined __CYGWIN__
#define MIDIFILE_PUBLIC __declspec(dllexport)
#elif defined BUILDING_MIDIFILE
#define MIDIFILE_PUBLIC __attribute__ ((visibility("default")))
#elif defined __CYGWIN__
#define MIDIFILE_PUBLIC __declspec(dllimport)
#else
#define MIDIFILE_PUBLIC
#endif

/* $Id: midifile.h,v 1.3 1991/11/03 21:50:50 piet Rel $ */
/* definitions for MIDI file parsing code */
MIDIFILE_PUBLIC extern int (*Mf_getc)();
MIDIFILE_PUBLIC extern void (*Mf_header)();
MIDIFILE_PUBLIC extern void (*Mf_starttrack)();
MIDIFILE_PUBLIC extern void (*Mf_endtrack)();
MIDIFILE_PUBLIC extern void (*Mf_on)();
MIDIFILE_PUBLIC extern void (*Mf_off)();
MIDIFILE_PUBLIC extern void (*Mf_pressure)();
MIDIFILE_PUBLIC extern void (*Mf_parameter)();
MIDIFILE_PUBLIC extern void (*Mf_pitchbend)();
MIDIFILE_PUBLIC extern void (*Mf_program)();
MIDIFILE_PUBLIC extern void (*Mf_chanpressure)();
MIDIFILE_PUBLIC extern void (*Mf_sysex)();
MIDIFILE_PUBLIC extern void (*Mf_metamisc)();
MIDIFILE_PUBLIC extern void (*Mf_sqspecific)();
MIDIFILE_PUBLIC extern void (*Mf_seqnum)();
MIDIFILE_PUBLIC extern void (*Mf_text)();
MIDIFILE_PUBLIC extern void (*Mf_eot)();
MIDIFILE_PUBLIC extern void (*Mf_timesig)();
MIDIFILE_PUBLIC extern void (*Mf_smpte)();
MIDIFILE_PUBLIC extern void (*Mf_tempo)();
MIDIFILE_PUBLIC extern void (*Mf_keysig)();
MIDIFILE_PUBLIC extern void (*Mf_arbitrary)();
MIDIFILE_PUBLIC extern void (*Mf_error)();
MIDIFILE_PUBLIC extern long Mf_currtime;
MIDIFILE_PUBLIC extern int Mf_nomerge;
MIDIFILE_PUBLIC void mfread(void);
MIDIFILE_PUBLIC void midifile(void);

/* definitions for MIDI file writing code */
MIDIFILE_PUBLIC extern int Mf_RunStat;
MIDIFILE_PUBLIC extern int (*Mf_putc)();
MIDIFILE_PUBLIC extern void (*Mf_wtrack)();
MIDIFILE_PUBLIC extern void (*Mf_wtempotrack)();
MIDIFILE_PUBLIC float mf_ticks2sec(unsigned long ticks, int division,
        unsigned int tempo);
MIDIFILE_PUBLIC unsigned long mf_sec2ticks(float secs, int division,
        unsigned int tempo);
MIDIFILE_PUBLIC void mfwrite();
MIDIFILE_PUBLIC int mf_w_midi_event(unsigned long delta_time,
        unsigned int type, unsigned int chan, unsigned char *data,
        unsigned long size);
MIDIFILE_PUBLIC int mf_w_meta_event(unsigned long delta_time,
        unsigned char type, unsigned char *data, unsigned long size);
MIDIFILE_PUBLIC int mf_w_sysex_event(unsigned long delta_time,
        unsigned char *data, unsigned long size);
MIDIFILE_PUBLIC void mf_w_tempo(unsigned long delta_time,
        unsigned long tempo);

/* MIDI status commands most significant bit is 1 */
#define note_off                0x80
#define note_on                 0x90
#define poly_aftertouch         0xa0
#define control_change          0xb0
#define program_chng            0xc0
#define channel_aftertouch      0xd0
#define pitch_wheel             0xe0
#define system_exclusive        0xf0
#define delay_packet            (1111)

/* 7 bit controllers */
#define damper_pedal            0x40
#define portamento              0x41
#define sostenuto               0x42
#define soft_pedal              0x43
#define general_4               0x44
#define hold_2                  0x45
#define general_5               0x50
#define general_6               0x51
#define general_7               0x52
#define general_8               0x53
#define tremolo_depth           0x5c
#define chorus_depth            0x5d
#define detune                  0x5e
#define phaser_depth            0x5f

/* parameter values */
#define data_inc                0x60
#define data_dec                0x61

/* parameter selection */
#define non_reg_lsb             0x62
#define non_reg_msb             0x63
#define reg_lsb                 0x64
#define reg_msb                 0x65

/* Standard MIDI Files meta event definitions */
#define meta_event              0xFF
#define sequence_number         0x00
#define text_event              0x01
#define copyright_notice        0x02
#define sequence_name           0x03
#define instrument_name         0x04
#define lyric                   0x05
#define marker                  0x06
#define cue_point               0x07
#define channel_prefix          0x20
#define end_of_track            0x2f
#define set_tempo               0x51
#define smpte_offset            0x54
#define time_signature          0x58
#define key_signature           0x59
#define sequencer_specific      0x7f

/* Manufacturer’s ID number */
#define Seq_Circuits (0x01) /* Sequential Circuits Inc. */
#define Big_Briar    (0x02) /* Big Briar Inc.           */
#define Octave       (0x03) /* Octave/Plateau           */
#define Moog         (0x04) /* Moog Music               */
#define Passport     (0x05) /* Passport Designs         */
#define Lexicon      (0x06) /* Lexicon                  */
#define Tempi        (0x20) /* Bon Tempi                */
#define Siel         (0x21) /* S.I.E.L.                 */
#define Kawai        (0x41) 
#define Roland       (0x42)
#define Korg         (0x42)
#define Yamaha       (0x43)

/* miscellaneous definitions */
#define MThd 0x4d546864L
#define MTrk 0x4d54726bL
#define lowerbyte(x) ((unsigned char)(x & 0xff))
#define upperbyte(x) ((unsigned char)((x & 0xff00)>>8))

#ifdef __cplusplus
}
#endif

#endif
