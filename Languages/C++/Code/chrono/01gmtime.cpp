#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    std::time_t now = std::time(nullptr);
    char *t = ctime(&now);
    cout << t << endl;
    cout << " ------------- " << endl;

    std::tm *tm = std::gmtime(&now);
    cout << tm->tm_gmtoff << endl;
    cout << tm->tm_zone << endl;
    cout << tm->tm_year << endl;
    cout << tm->tm_mon << endl;
    cout << tm->tm_mday << endl;
    cout << tm->tm_hour << endl;
    cout << tm->tm_min << endl;
    cout << tm->tm_sec << endl;
    // int	tm_sec;		/* seconds after the minute [0-60] */
    // int	tm_min;		/* minutes after the hour [0-59] */
    // int	tm_hour;	/* hours since midnight [0-23] */
    // int	tm_mday;	/* day of the month [1-31] */
    // int	tm_mon;		/* months since January [0-11] */
    // int	tm_year;	/* years since 1900 */
    // int	tm_wday;	/* days since Sunday [0-6] */
    // int	tm_yday;	/* days since January 1 [0-365] */
    // int	tm_isdst;	/* Daylight Savings Time flag */
    // long	tm_gmtoff;	/* offset from UTC in seconds */
    // char	*tm_zone;	/* timezone abbreviation */

    return 0;
}