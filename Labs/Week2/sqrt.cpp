/*******************************************************************************
* Filename: sqrt.cpp
 * Author  : Syed Ahmad Shah
 * Version : 1.0
 * Date    : September 11, 2024
 * Description: Computes the GCD of two command-line arguments.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/


#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

// define sqrt func, default epsilon to 1e-7 if no value is provided by user
double sqrt(double num, double epsilon = 1e-7) {
    // create necessary variables as per function
    double difference;
    double lastGuess = 1;
    double n = num;
    double nextGuess;

    if (num == 0 or num == 1) {
        return num;
    }else if (num < 0) {
        return numeric_limits<double>::quiet_NaN();
    }

    do {
        nextGuess = ((n/lastGuess) + lastGuess)/2;
        difference = abs(lastGuess - nextGuess);

        lastGuess = nextGuess;
    }
    while(difference > epsilon);

    return lastGuess;
}


int main(int argc, char *argv[]) {
    double m;
    double n = 1e-7;
    istringstream iss;

    // if the amount of arguments is less than 2 or is greater than 3 inform the user of the correct usage format
    if(argc < 2 || argc > 3) {
        cerr << "Usage: ./sqrt <value> [epsilon]"<< endl;
        return 1;
    }

    // clear iss for extraction and storing the first argument
    iss.clear();
    iss.str(argv[1]);
    if(!(iss >> m)) {
        cerr << "Error: Value argument must be a double." <<endl;
        return 1;
    }

    // If a second argument is provided proceed
    if(argv[2]){
        // clear iss
        iss.clear();
        iss.str(argv[2]);

        // if epsilon is not able to be stored into iss, or n is less than 0 throw error
        if(!(iss >> n) or n <= 0) {
            cerr << "Error: Epsilon argument must be a positive double." <<endl;
            return 1;
        }
    }

    cout << fixed << setprecision(8) << sqrt(m, n) << endl;
    return 0;

}
