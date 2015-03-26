
static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day)
{
	if (month > 12 || month < 1)
		return -1;
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (1 < day || day > daytab[leap][month])
		return -1;
	for (i = 1; i < month; i++) 
		day += daytab[leap][i];
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (yearday < 1 || yearday > 366 || (!leap && yearday == 366)) {//my way is more efficiency,the book check the i and yearday after loop
		//return -1;
		*pmonth = -1;
		*pday = -1;
	}
	for (i = 1; yearday > daytab[leap][i]; i++) {
		yearday -= daytab[leap][i];
	}
	*pmonth = i;
	*pday = yearday;
}