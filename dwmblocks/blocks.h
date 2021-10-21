//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/

	{"| ", "date '+%F (%a) %r'",					1,		0},
	
	{"|  ", "cat /proc/net/wireless | awk 'NR==3 {print $3}' | cut -b 1,2", 5,             0},
	
	{"|  ", "top -b -n1 | grep 'Cpu(s)' | awk '{print $2 + $4 }'", 5, 0},
	
	{"|  ", "free -h --si | awk '/^Mem/ { print $3\"/\"$2 }' ",	1,		0},

	{"|  ", "tempcheck", 5, 0},

	{"|  ", "cat /sys/class/power_supply/BAT1/capacity", 30, 0},

	{"", "batterycheck", 1, 0}, 

	{"|  ", "bluetoothcheck", 1, 0},

	{"", "echo '|' ", 0, 0},

};


//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " ";
static unsigned int delimLen = 5;
