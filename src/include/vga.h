#ifndef VGA_H
#define VGA_H
// definitions for the VGA hardware.

// 4 bit color codes

#define VGA_BLK (ubyte) 0x0
#define VGA_BLU (ubyte) 0x1	
#define VGA_GRN (ubyte) 0x2
#define VGA_CYN (ubyte) 0x3
#define VGA_RED (ubyte) 0x4
#define VGA_MGT (ubyte) 0x5
#define VGA_BRN (ubyte) 0x6
#define VGA_LGR	(ubyte) 0x7
#define VGA_DGR	(ubyte) 0x8
#define VGA_LBL (ubyte) 0x9
#define VGA_LGN (ubyte) 0xA
#define VGA_LCY (ubyte) 0xB
#define VGA_LRD (ubyte) 0xC
#define VGA_LMG (ubyte) 0xD
#define VGA_LBR (ubyte) 0xE
#define VGA_WHI	(ubyte) 0xF

// Attribute byte macro
#define ATTRIB(b, f) (ubyte) (b << 4 | f & 0x0F)

// VGA IO ports.
// IN 	- Port should be read from
// OUT	- Port should be written to
// CTL	- Address port, should be written to.
// IO	- Bidirectional port.

#define VGA_IO_CRT0_CTL (uword) 0x3B4
#define VGA_IO_CRT0_OUT (uword) 0x3B5
#define VGA_IO_STAT_IN  (uword) 0x3BA
#define VGA_IO_FEAT_CTL	(uword) 0x3BA	// NOTE: This is the same port as last, its function changes depending on whether you're reading or writing.
#define VGA_IO_ATTR_CTL	(uword) 0x3C0
#define VGA_IO_ATTR_IN	(uword) 0x3C1
#define VGA_IO_ISR0_IN	(uword) 0x3C2	
#define VGA_IO_MISC_OUT (uword) 0x3C2	// This is read at 0x3CC
#define VGA_IO_SEQ_CTL	(uword) 0x3C4
#define VGA_IO_SEQ_IN	(uword) 0x3C5
#define VGA_IO_DAC_IN	(uword) 0x3C7	// DAC state register
#define VGA_IO_DAC_RD	(uword) 0x3C7	// Address read mode
#define VGA_IO_DAC_CTL	(uword) 0x3C8	// DAC address write mode reg
#define VGA_IO_DAC_OUT	(uword) 0x3C9	// Color codes written here after writing address index to 0x3C8
#define VGA_IO_FEAT_IN	(uword) 0x3CA
#define VGA_IO_MISC_IN	(uword) 0x3CC	
#define VGA_IO_GCR_CTL	(uword) 0x3CE
#define VGA_IO_GCR_OUT	(uword) 0x3CF
#define VGA_IO_CRT1_CTL	(uword) 0x3D4	// These are the standard ports, but note there are duplicates at 3B4h and 3B5h
#define VGA_IO_CRT1_OUT	(uword) 0x3D5

// VGA IO indices.

// CRTC Address register indices
// For information, go to http://www.osdever.net/FreeVGA/vga/crtcreg.htm

#define VGA_IDX_CRTC_HTR 	(ubyte) 0x00	// Horizontal total register
#define VGA_IDX_CRTC_EHDR	(ubyte) 0x01	// End horizontal display register
#define VGA_IDX_CRTC_SHBR	(ubyte) 0x02	// Start horizontal blanking register
#define VGA_IDX_CRTC_EHBR	(ubyte) 0x03	// End horizontal blanking register
#define VGA_IDX_CRTC_SHRR	(ubyte) 0x04	// Start horizontal retrace register
#define VGA_IDX_CRTC_EHRR	(ubyte) 0x05	// End horizontal retrace register
#define VGA_IDX_CRTC_VTR	(ubyte) 0x06	// Vertical total register
#define VGA_IDX_CRTC_OFR	(ubyte) 0x07	// Overflow register
#define VGA_IDX_CRTC_PRSR	(ubyte) 0x08	// Preset row scan register
#define VGA_IDX_CRTC_MSLR	(ubyte) 0x09	// Maximum scan line register
#define VGA_IDX_CRTC_CSR	(ubyte) 0x0A	// Cursor start register
#define VGA_IDX_CRTC_CER	(ubyte) 0x0B	// Cursor end register
#define VGA_IDX_CRTC_SAHR	(ubyte) 0x0C	// Start address high register
#define VGA_IDX_CRTC_SALR	(ubyte) 0x0D	// Start address low register
#define VGA_IDX_CRTC_CLHR	(ubyte) 0x0E	// Cursor location high register
#define VGA_IDX_CRTC_CLLR	(ubyte) 0x0F	// Cursor location low register
#define VGA_IDX_CRTC_VRSR	(ubyte) 0x10	// Vertical retrace start register
#define VGA_IDX_CRTC_VRER	(ubyte) 0x11	// Vertical retrace end register
#define VGA_IDX_CRTC_VDER	(ubyte) 0x12	// Vertical display end register
#define VGA_IDX_CRTC_OSR	(ubyte) 0x13	// Offset register
#define VGA_IDX_CRTC_ULLR	(ubyte) 0x14	// Underline location register
#define VGA_IDX_CRTC_SVBR	(ubyte) 0x15	// Start vertical blanking register
#define VGA_IDX_CRTC_EVBR	(ubyte) 0x16	// End vertical blanking register
#define VGA_IDX_CRTC_CMCR	(ubyte) 0x17	// CRTC mode control register
#define VGA_IDX_CRTC_LCR	(ubyte) 0x18	// Line compare register

// Sequencer register indices.
// For information, see http://www.osdever.net/FreeVGA/vga/seqreg.htm

#define VGA_IDX_SEQ_RST		(ubyte) 0x00	// Reset register
#define VGA_IDX_SEQ_CLK		(ubyte) 0x01	// Clock mode register
#define VGA_IDX_SEQ_MASK	(ubyte) 0x02	// Map mask register
#define VGA_IDX_SEQ_CMSR	(ubyte) 0x03	// Character map select register
#define VGA_IDX_SEQ_SMMR	(ubyte) 0x04	// Sequencer memory mode register

// Graphic register indices
// For information, se http://osdever.net/FreeVGA/vga/graphreg.htm

#define VGA_IDX_GCR_SRS		(ubyte) 0x00	// Set/reset register
#define VGA_IDX_GCR_SRSE	(ubyte) 0x01	// Enable set/reset
#define VGA_IDX_GCR_CCR		(ubyte) 0x02	// Color compare register
#define VGA_IDX_GCR_DRR		(ubyte) 0x03	// Data rotate register
#define VGA_IDX_GCR_RMSR	(ubyte) 0x04	// Read map select register
#define VGA_IDX_GCR_GMR		(ubyte) 0x05	// Graphics mode register
#define VGA_IDX_GCR_MGR		(ubyte) 0x06	// Miscellaneous graphics register
#define VGA_IDX_GCR_CDCR	(ubyte) 0x07	// Color don't care register
#define VGA_IDX_GCR_BMR		(ubyte) 0x08	// Bit mask register



// 4 bit screen dimensions
#define VGA_X	80
#define VGA_Y	25

// Globally accessible VGA functions


#endif
