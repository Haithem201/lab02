#include <iostream>
#include <iomanip>

class Time {
public:
    Time(int seconds = 0) : m_seconds(seconds) {}

    int getSeconds() const {
        return m_seconds;
    }

    void setSeconds(int seconds) {
        m_seconds = seconds;
    }

    void display() const {
        const int hours = m_seconds / 3600;
        const int minutes = (m_seconds % 3600) / 60;
        const int seconds = m_seconds % 60;

        std::cout << std::setfill('0') << std::setw(2) << hours << "h:"
                  << std::setfill('0') << std::setw(2) << minutes << "m:"
                  << std::setfill('0') << std::setw(2) << seconds << "s";
    }

    friend std::istream& operator>>(std::istream& is, Time& t) {
        int hours, minutes, seconds;
        char separator;

        if (is >> hours >> separator >> minutes >> separator >> seconds) {
            t.m_seconds = hours * 3600 + minutes * 60 + seconds;
        } else {
            is.setstate(std::ios::failbit);
        }

        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        t.display();
        return os;
    }

    Time operator+(const Time& other) const {
        return Time(m_seconds + other.m_seconds);
    }

    Time operator-(const Time& other) const {
        return Time(m_seconds - other.m_seconds);
    }

    Time operator*(int scalar) const {
        return Time(m_seconds * scalar);
    }

    explicit operator int() const {
        return m_seconds;
    }

private:
    int m_seconds;
};

int main() {
    const Time t1(200);
    std::cout << t1 << std::endl; // Displays 00h:03m:20s.

    Time t2;
    if (!(std::cin >> t2)) { // Handle input error.
        std::cerr << "Invalid input. Please try again." << std::endl;
        return 1;
    }

    const Time t3 = t2 - t1;
    std::cout << t3 << std::endl; // Displays the difference between t2 and t1.

    const int t3s = static_cast<int>(t3);
    std::cout << t3s << std::endl; // Displays the total seconds of t3.

    const Time t4 = t1 * 2;
    std::cout << t4 << std::endl; // Displays the doubled time of t1.

    return 0;
}
