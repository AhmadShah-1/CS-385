

#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

int max(int n, int m){
    if(n>m){
        return n;
    }
    return m;

}
int main(int argc, char* argv[]){
    int n, m;
    // This wil act as a keyboard
    // This is used here to convert strign to int
    istringstream iss;

    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <int> <int>" << endl;
        return 1;
    }

    // The str is written into iss
    iss.str(argv[1]);

    // iss knows what type n is so it knows what type to convert it to
    // iss >> n;

    if(!(iss >> n)){
        cerr << "Error: The first argument must be an int." << endl;
        return 1;
    }

    // After using iss to convert the first one, you have to clear out the garbage to convert another thing
    iss.clear();
    iss.str(argv[2]);
    if(!(iss >> m)){
        cerr << "Error: The second argument must be an int." << endl;
        return 1;
    }

    cout<< "n is " << n << " and m is " << m << endl;
    cout << "max()" << n << ", " << m << ")" << max(n, m) << endl;



    return 0;
}

