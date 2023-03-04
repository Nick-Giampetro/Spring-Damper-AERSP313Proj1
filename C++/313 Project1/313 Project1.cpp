/*
    Ok I will try to make a MATLAB version of this if I find time this week to do that. I am just much, MUCH more comfortable with C++ so that is what I decided to use for now.
    HOWEVER, I am like 99% sure that my algorithms for RK2 and explicit euler are correct since i just ripped them out of the book and they get results consistent with each other.
    I put long dashed lines in comments around the areas for "inputs" into the program to solve different ODEs and with differnt steps.
    Obviously if you are feeling adventurous you can inspect the rest of the code to see how it works and if I made any critical mistakes fix it and let me know.
    If you need help using the code go ahead and text me but I tried to make it as clear as I possibly could.
    The data file will be saved into the VSS project file on your PC.
        - Nick
    
    feel free to add your own comments here or below
*/



//  import and std namespace
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

//  global variables
double e = 2.718281;

//  yPrime functions bodies under the main function
double y1Prime(double, double, double);
double y2Prime(double, double, double);
// double exact(double);

//  ODE functions, bodies under main function
void rk2(double[], double[], double[], double, int);
//void eEuler(double[], double[], double[], double, int);

int heaviside(double, double);


//  main function
int main()
{


    //--------------------------------------------------------------------
    const int s = 1000000;                    //    enter number of steps here 
    const double h = 0.00001;                //    and step size here
    // -------------------------------------------------------------------


    // variable and array declaration
    const int a = s + 1;
    static double y1[a], y2[a], x[a];
    x[0] = 0;
    x[1] = h;


    //--------------------------------------------------------------------
    y1[0] = 0;                      //       enter initial conditions here
    y2[0] = 0;                      //  
    // -------------------------------------------------------------------


    //console header
    cout << "X" << setw(20) << "Y" << setw(20) << "Y'" << endl;

    // function eEuler solves ODE using euler method
    //eEuler(x, y1, y2, h, s);


    // prints a line for organization
    cout << endl;
    for (int i = 0; i < 50; i++) {
        cout << "-";
    }
    cout << endl << endl ;


    // function rk2 solves ODE using rk2
    rk2(x, y1, y2, h, s);


    // you can get rid of this if you want just ensure the console pauses for me bc I messed up my VSS
    system("pause");
}





//  y' function goes in here
double y1Prime(double x, double y1, double y2) {
    double yPrime;

    //-------------------------------------------------------------------------------------
    yPrime = y2;               // set yPrime equal to y' function in terms of x, y1, and y2
    //-------------------------------------------------------------------------------------

    return yPrime;
}






//  y" function goes in here
double y2Prime(double x, double y1, double y2) {
    double yDoublePrime;

    //---------------------------------------------------------------------------------------------------------------------
    yDoublePrime = heaviside(x,0) - 4 * y1 - 0.2 * y2;               // set yDoublePrime equal to y'' function in terms of x, y1, and y2
    //---------------------------------------------------------------------------------------------------------------------

    return yDoublePrime;
}


//  calculated exact solution goes here to compare
double exact(double x) {
    double exact;

    // use this to set the terms of the exact soln' currently exact is probably wrong
    double w = 2 * sqrt(1 - .05 * .05), C = 10 * w;

    // exact solution NEEDS TO BE CHANGED TO ACTUAL EXACT SOLUTUION
    exact = C * pow(e, (-.05 * 2 * x)) * sin(w * x);

    return exact;
}



//---------------------------------------------------GO BELOW AT YOUR OWN RISK----------------------------------------------------------------------------------


// rk2 function, it need not to be observed or understood just trust it ---- unless of course you can tell that i am super wrong then fix it thanks
void rk2(double x[], double y1[], double y2[], double h, int s) {
    double K, L, k1, k2, k3, k4;

    //opens data file so you can use excel to analyze results
    ofstream file;
    file.open("RK2Num.csv");
    file << "X" << ',' << "Y" << ',' << "Y'" << endl;

    //loop that runs the RK2 algorithm
    for (int n = 0; n < (s); n++) {
       
        //i is the index of the next n value, n+1
        int i = n + 1;

        //x increment
        x[i] = x[n] + h;


        //math
        k1 = h / 2 * y2Prime(x[n], y1[n], y2[n]);
        K = h / 2 * (y2[n] + k1 / 2);
        k2 = h / 2 * y2Prime((x[n] + h / 2), (y1[n] + K), (y2[n] + k1));
        k3 = h / 2 * y2Prime((x[n] + h / 2), (y1[n] + K), (y2[n] + k2));
        L = h * (y2[n] + k3);
        k4 = h / 2 * y2Prime((x[n] + h), (y1[n] + L), (y2[n] + k3 * 2));


        //more math
        y1[i] = y1[n] + h * (y2[n] + (k1 + k2 + k3) / 3);
        y2[i] = y2[n] + (k1 + 2 * k2 + 2 * k3 + k4) / 3;


        // output to file and console
        file << x[i] << ',' << y1[i] << ',' << y2[i] << endl;
        //cout << x[i] << setw(20) << y1[i] << setw(20) << y2[i] << setw(20) << exact(x[i]) << endl;
    }

    cout << x[s] << setw(20) << y1[s] << setw(20) << y2[s] << setw(20) << exact(x[s]) << endl;

    //closes file
    file.close();
}



// explicit Euler function
void eEuler(double x[], double y1[], double y2[], double h, int s) {

    //opens data file so you can use excel to analyze results
    ofstream file;
    file.open("eulerNum.csv");
    file << "X" << ',' << "Y" << ',' << "Y'" << endl;

    //loop that runs the explicit euler algorithm
    for (int n = 0; n < (s); n++) {
        
        //i is the index of the next n value, n+1
        int i = n + 1;

        //x increment
        x[i] = x[n] + h;


        //math
        y1[i] = y1[n] + h * y1Prime(x[n], y1[n], y2[n]);
        y2[i] = y2[n] + h * y2Prime(x[n], y1[n], y2[n]);


        //output to file and console
        file << x[i] << ',' << y1[i] << ',' << y2[i] << endl;
        cout << x[i] << setw(20) << y1[i] << setw(20) << y2[i] << endl;
    }

    //closes file
    file.close();
}

int heaviside(double x, double a) {
        if ((x - a) > 0.0)
        return 1;
    else
        return 0;
} 