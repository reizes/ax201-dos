
static void (__interrupt __far *old_int09)();
static void __interrupt __far new_int09();
void init_key(void);
void del_key(void);

static unsigned char scan[128], asci[128];

// Keyboard interrupt....
void init_key(void)
{
	memset(scan, 0, 128);
	memset(asci, 0, 128);

	old_int09 = _dos_getvect(0x09);
	_dos_setvect(0x09,new_int09);
}

void del_key(void)
{
	_dos_setvect(0x09,old_int09);
}

static void __interrupt __far new_int09()
{
	unsigned char port, code;

	_disable();

	port = inp(0x60);
	code = port & 127;

	if ((port < 128) && (scan[code] == 0)) {
		scan[code] = 1;
		asci[code] = 1;
	}
	else if(port > 127)     scan[code] = 0;

	outp(0x20, 0x20);

	_enable();
}
// Keyboard interrupt End


