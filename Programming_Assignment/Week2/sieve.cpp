/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Syed Ahmad Shah
 * Date        : 9/15/2024
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>


using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the requirements document.

    // Find neccessary info for primes per row
    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80/(max_prime_width+1);

    // Find the number of primes located in is_prime
    int numberofprimes = 0;
    for(int i = 0; i <= limit_; i++) {
        if(is_prime_[i] == true) {
            numberofprimes++;
        }
    }

    cout<<"Number of primes found: " << numberofprimes << endl;
    cout<<"Primes up to " << limit_ << ":"<< endl;

    // If the number of primes that exists is over the number of primes that should exist do the following code else,
    if(numberofprimes > primes_per_row) {
        int prime_count = 0;
        // create bool to track if the number is the first number of the line
        bool firstnumber = true;

        for(int i = 0; i <= limit_; i++) {
            if(is_prime_[i] == true) {
                // if its the first number do the appropriate spacing
                if(firstnumber == true){
                    cout<< setw(max_prime_width) << i;
                    firstnumber = false;
                    prime_count++;

                }else{
                    cout<< setw(max_prime_width +  1) << i;
                    prime_count++;
                
                    if(prime_count % primes_per_row == 0) {
                        cout<<endl;
                        firstnumber = true;
                }
                }
            }
        }
    }else {
        for(int i = 0; i <= limit_; i++) {
            if(is_prime_[i] == true) {
                if(i != max_prime_){
                    cout<< i << " ";
                }else{
                    cout<<i;
                }

            }
            
        }
    }
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.

    // create values in is_prime and fill it with true
    for(int i = 0; i <= limit_; i++) {
        is_prime_[i] = true;
    }

    // make 1 and 2 false
    is_prime_[0] = false;
    is_prime_[1] = false;

    // program for sieve
    for(int i = 2; i <= sqrt(limit_); i++) {
        if(is_prime_[i] == true) {
            for(int j = pow(i, 2); j <= limit_; j += i) {
                is_prime_[j] = false;
            }
        }
    }


    for(int i = limit_; i >= 0; i--) {
        if(is_prime_[i] == true) {
            max_prime_ = i;
            break;
        }
    }


}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.

    // iterate until you can no longer divide the num by 10
    int counter = 0;
    while(num > 0) {
        num /= 10;
        counter += 1;
    }

    return counter;
}

int main() {


    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    cout<<endl;
    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve sieve(limit);
    sieve.display_primes();

    return 0;

}
