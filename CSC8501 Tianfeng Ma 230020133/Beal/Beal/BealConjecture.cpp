#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <thread>
#include <atomic>
#include <set>

using namespace std;
atomic<bool> shouldTerminate(false);
#define MAX 200
struct MyData {
    int value;
    friend istream& operator>>(std::istream& in, MyData& data) {
        in >> data.value;
        return in;
    }
};
struct BntStore {
    int bnt;
    int a;
    int b;
    int c;
    int x;
    int y;
    int z;
};
typedef struct
{
    int len;
    int s[MAX + 1];
} hp;
bool compareByBnt(const BntStore& a, const BntStore& b) 
{    
    return a.bnt < b.bnt;
}
template <typename T>
void input(T* a, int x) {
    int i;

    a->len = 0;

    while (x > 0) {
        a->s[1 + a->len++] = x % 10;
        x /= 10;
    }

    for (i = a->len + 1; i <= MAX; i++)
        a->s[i] = 0;
}
void print(hp* y) 
{
    int i;
    for (i = y->len; i >= 1; i--)
        printf("%d", y->s[i]);
    printf("\n");
}
template <typename T>
void add(const T* a, const T* b, T* c) {
    int i, len;

    for (i = 1; i <= MAX; i++) c->s[i] = 0;

    if (a->len > b->len) len = a->len;
    else len = b->len;

    for (i = 1; i <= len; i++) {
        c->s[i] += a->s[i] + b->s[i];
        if (c->s[i] >= 10) {
            c->s[i] -= 10;
            c->s[i + 1]++;
        }
    }

    if (c->s[len + 1] > 0) len++;
    c->len = len;
}
template <typename T>
void multiplyh(const T* a, const T* b, T* c) {
    int i, j, len;

    for (i = 1; i <= MAX; i++) c->s[i] = 0;

    for (i = 1; i <= a->len; i++) {
        for (j = 1; j <= b->len; j++) {
            c->s[i + j - 1] += a->s[i] * b->s[j];
            c->s[i + j] += c->s[i + j - 1] / 10;
            c->s[i + j - 1] %= 10;
        }
    }

    len = a->len + b->len + 1;
    while (len > 1 && c->s[len] == 0) len--;
    c->len = len;
}
template <typename T>
void power(const T* a, int b, T* c) {
    T e;

    if (b == 0) {
        c->len = 1;
        c->s[1] = 1;
    }
    else if (b == 1) {
        memcpy(c, a, sizeof(T));
    }
    else {
        power(a, b / 2, &e);
        multiplyh(&e, &e, c);

        if (b % 2 == 1) {
            memcpy(&e, c, sizeof(T));
            multiplyh(&e, a, c);
        }
    }
}
template <typename T>
int compare(const T* a, const T* b) {
    int len;

    if (a->len > b->len) len = a->len;
    else len = b->len;

    while (len > 0 && a->s[len] == b->s[len]) len--;

    if (len == 0) return 0;
}
void playAnimation() 
{
    
    system("cls");
    int dotCount = 0;
    string animationPrefix = "Processing";
    while (!shouldTerminate)
    {
        if (dotCount == 6) {
            std::cout << "                    \r" << std::flush;
            dotCount = 0;
        }
        std::string dots(dotCount, '.');
        std::cout << animationPrefix << dots << "\r" << std::flush;
        dotCount++;

        this_thread::sleep_for(std::chrono::milliseconds(800));
    }
}

class BealConjecture
{
public:
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    int gcdOfThree(int a, int b, int c) {
        int result = gcd(a, b);
        result = gcd(result, c);
        return result;
    }
    int CalulateBNTs(int a, int b, int c, int x, int y, int z)
    {
        int Bnts = a + b + c + x + y + z;
        return Bnts;
    }

    virtual vector<BntStore> isBealConjectureSatisfied(int abcMin, int abcMax, int xyzMin, int xyzMax, int BntsNeedNum)
    {

        int a, b, c, x, y, z;
        int BntsCount = 0;                                                                                                                                                                                                                                                 
        ofstream outFile("my_data.txt");
        outFile << "Solution to Problem 1" << endl;
        vector<BntStore> data;
        for (a = abcMin; a < abcMax; a++) {

            for (b = abcMin; b < a + 1; b++) {

                for (c = abcMin; c < abcMax; c++) {

                    for (x = xyzMin; x < xyzMax; x++) {

                        for (y = xyzMin; y < xyzMax; y++) {

                            for (z = xyzMin; z < xyzMax; z++)
                            {
                                if ((int)(pow(a, x) + 0.5) + (int)(pow(b, y) + 0.5) == (int)(pow(c, z) + 0.5))
                                {
                                    int greatestCommonDivisor = gcdOfThree(a, b, c);
                                    if (greatestCommonDivisor > 1)
                                    {
                                        int Bnt = CalulateBNTs(a, b, c, x, y, z);
                                        BntsCount++;
                                        data.push_back({ Bnt, a, b, c, x, y, z });
                                      
                                        if (BntsCount == BntsNeedNum)
                                        {
                                            sort(data.begin(), data.end(), compareByBnt);
                                            return data;
                                        }
                                    }

                                }

                            }

                        }

                    }

                }

            }

        }
        
        outFile.close(); 
    }
};
class BealConjecture01 : public BealConjecture {
public:
    bool isPrime(int n) {
        if (n <= 1) {
            return false; 
        }
        if (n <= 3) {
            return true; 
        }
        if (n % 2 == 0 || n % 3 == 0) {
            return false; 
        }
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false; 
            }
        }
        return true;
    }

    vector<BntStore>isBealConjectureSatisfied(int abcMin, int abcMax, int xyzMin, int xyzMax, int BntsNeedNum) override
    {
        int a, b, c, x, y, z;
        vector<BntStore> data;
        ofstream outFile("my_data.txt", ios::app);
        outFile << "Solution to Problem 2" << endl;
        for (a = abcMin; a < abcMax; a++) {

            for (b = abcMin; b < a + 1; b++) {

                for (c = abcMin; c < abcMax; c++) {

                    for (x = xyzMin; x < xyzMax; x++) {

                        for (y = xyzMin; y < xyzMax; y++) {

                            for (z = xyzMin; z < xyzMax; z++)
                            {
                                if ((int)(pow(a, x) + 0.5) + (int)(pow(b, y) + 0.5) == (int)(pow(c, z) + 0.5))
                                {
                                    int greatestCommonDivisor = gcdOfThree(a, b, c);
                                    if (greatestCommonDivisor > 1)
                                    {
                                        int Bnt = CalulateBNTs(a, b, c, x, y, z);
                                        if (isPrime(Bnt))
                                        {
                                                data.push_back({ Bnt, a, b, c, x, y, z });
                                                                                              
                                                    
                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }
        
        outFile.close();
        sort(data.begin(), data.end(), compareByBnt);
        set<BntStore, decltype(compareByBnt)*> uniqueBntSet(compareByBnt);
        for (const BntStore& item : data) {
            uniqueBntSet.insert(item);
        }
       vector<BntStore> result(uniqueBntSet.begin(), uniqueBntSet.end());
        if (result.size() > 5) {
            result.resize(5);
        }
        return result;
        
    }
};
class BealConjecture02 : public BealConjecture
{
    public:
    vector<BntStore> isBealConjectureSatisfied(int abcMin, int abcMax, int xyzMin, int xyzMax, int BntsNeedNum) override
    {

        int a, b, c, x, y, z;
        ofstream outFile("my_data.txt", ios::app);
        outFile << "Solution to Problem 3" << endl;
        vector<BntStore> data;
        for (a = abcMin; a < abcMax; a++) {

            for (b = abcMin; b < a + 1; b++) {

                for (c = abcMin; c < abcMax; c++) {

                    for (x = xyzMin; x < xyzMax; x++) {

                        for (y = xyzMin; y < xyzMax; y++) {

                            for (z = xyzMin; z < xyzMax; z++)
                            {
                                hp A,B,C,result1,result2,result3,addResult;
                                input(&A, a);input(&B, b);input(&C, c);
                                power(&A, x, &result1);power(&B, y, &result2);power(&C, z, &result3);
                                add(&result1, &result2, &addResult);
                                if (compare(&addResult, &result3) == 0)
                                {
                                    int Bnt = CalulateBNTs(a, b, c, x, y, z);
                                    data.push_back({ Bnt, a, b, c, x, y, z });
                                   
                     
                                }

                            }

                        }

                    }

                }

            }

        }
       
        outFile.close();
        sort(data.begin(), data.end(), compareByBnt);
        return data;
    }
    
};
class BealConjecture03 : public BealConjecture
{
public:
    bool isComposite(int n) {
        if (n <= 1) {
            return false; 
        }

        for (int i = 2; i <= n / 2; ++i) {
            if (n % i == 0) {
                return true; 
            }
        }

        return false; 
    }
    vector<BntStore> isBealConjectureSatisfied(int abcMin, int abcMax, int xyzMin, int xyzMax, int BntsNeedNum) override
    {

        int a, b, c, x, y, z;
        ofstream outFile("my_data.txt", ios::app);
        outFile << "Solution to Problem 5" << endl;
        vector<BntStore> data;
        for (a = abcMin; a < abcMax; a++) {

            for (b = abcMin; b < a + 1; b++) {

                for (c = abcMin; c < abcMax; c++) {

                    for (x = xyzMin; x < xyzMax; x++) {

                        for (y = xyzMin; y < xyzMax; y++) {

                            for (z = xyzMin; z < xyzMax; z++)
                            {
                                if ((int)(pow(a, x) + 0.5) + (int)(pow(b, y) + 0.5) == (int)(pow(c, z) + 0.5))
                                {
                                    int greatestCommonDivisor = gcdOfThree(a, b, c);
                                    if (greatestCommonDivisor > 1)
                                    {
                                        int Bnt = CalulateBNTs(a, b, c, x, y, z);
                                        if (isComposite(Bnt)) 
                                        {
                                            data.push_back({ Bnt, a, b, c, x, y, z });
                                           
                                        }
                                      
                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

        outFile.close();
        sort(data.begin(), data.end(), compareByBnt);
        set<BntStore, decltype(compareByBnt)*> uniqueBntSet(compareByBnt);
        for (const BntStore& item : data) {
            uniqueBntSet.insert(item);
        }
        vector<BntStore> result(uniqueBntSet.begin(), uniqueBntSet.end());
        if (result.size() > 10) {
            result.resize(10);
        }
        return result;
    }

};
class BealConjecture04 : public BealConjecture
{
public:
    void createAsciiHistogram(const std::vector<int>& data, int binWidth, int minRange, int maxRange) {
       

        if (data.empty()) {
            std::cout << "No data to create a histogram." << std::endl;
            
            return;
        }
        std::ofstream outFile("my_data.txt", ios::app);
        outFile << "Solution to Problem 7" << std::endl;
        int numBins = (maxRange - minRange) / binWidth + 1;

        std::vector<int> binCounts(numBins, 0);

        for (int value : data) {
            if (value >= minRange && value <= maxRange) {
                int binIndex = (value - minRange) / binWidth;
                binCounts[binIndex]++;
            }
        }
        cout << "-------Done!-------" << std::endl;
        for (int i = 0; i < binCounts.size(); ++i) {
            int binStart = minRange + i * binWidth;
            int binEnd = binStart + binWidth - 1;
            std::cout << binStart << "-" << binEnd << ": ";
            outFile << binStart << "-" << binEnd << ": ";
            for (int j = 0; j < binCounts[i]; ++j) {
                std::cout << '*';
                outFile << '*';
            }
            std::cout << std::endl;
            outFile << std::endl;
        }

        outFile.close();
    }
    void isBealConjectureSatisfied01(int abcMin, int abcMax, int xyzMin, int xyzMax,int MinBnt,int MaxBnt,int binWidth)
    {

        int a, b, c, x, y, z;
        vector<int> BntVector;
        int BntsCount = 0;
        for (a = abcMin; a < abcMax; a++) {

            for (b = abcMin; b < a + 1; b++) {

                for (c = abcMin; c < abcMax; c++) {

                    for (x = xyzMin; x < xyzMax; x++) {

                        for (y = xyzMin; y < xyzMax; y++) {

                            for (z = xyzMin; z < xyzMax; z++)
                            {
                                if ((int)(pow(a, x) + 0.5) + (int)(pow(b, y) + 0.5) == (int)(pow(c, z) + 0.5))
                                {
                                    int greatestCommonDivisor = gcdOfThree(a, b, c);
                                    if (greatestCommonDivisor > 1)
                                    {
                                        int Bnt = CalulateBNTs(a, b, c, x, y, z);
                                        if (Bnt >= MinBnt && Bnt <= MaxBnt)
                                            BntVector.push_back(Bnt);
                                    }

                                }

                            }

                        }

                    }

                }

            }

        }
        createAsciiHistogram(BntVector, binWidth,MinBnt,MaxBnt);
        
    }

};
class BealConjecture05 : public BealConjecture 
{
public:
    void findSquare() 
    {
        std::ofstream outFile("my_data.txt", ios::app);
        outFile << "Solution to Problem 7" << std::endl;
        for (int i = 32; i * i <= 100000; i++) {
            int square = i * i;
            std::cout << square << std::endl;
            outFile << square << std::endl;
        }
        outFile.close();
    }
    void findHighestBnt() 
    {
        int a =2, b =2, c =2, x=657, y=657, z=658;
        std::ofstream outFile("my_data.txt", ios::app);
        outFile << "Solution to Problem 7" << endl;
       
        hp A, B, C, result1, result2, result3, addResult;
        input(&A, a); input(&B, b); input(&C, c);
        power(&A, x, &result1); power(&B, y, &result2); power(&C, z, &result3);
        add(&result1, &result2, &addResult);
        if (compare(&addResult, &result3) == 0)
        {
            int Bnt = CalulateBNTs(a, b, c, x, y, z);
            cout << Bnt << ":" << a << ',' << x << ',' << b << ',' << y << ',' << c << ',' << z << "\n";     
            outFile << Bnt << ":" << a << ',' << x << ',' << b << ',' << y << ',' << c << ',' << z << "\n";
        }
        outFile.close();
    }
};
class ProblemSolver {
public:
    void QuestionPrinter(const std::vector<BntStore>& data) 
    {
        ofstream outFile("my_data.txt", ios::app);    
        for (const BntStore& item : data) {
            cout << item.bnt << ":" << item.a << ',' << item.x << ',' << item.b << ',' << item.y << ',' << item.c << ',' << item.z << "\n";
            outFile << item.bnt << ":" << item.a << ',' << item.x << ',' << item.b << ',' << item.y << ',' << item.c << ',' << item.z << "\n";
        }
        outFile.close();
    }
    void Question1()
    {
        BealConjecture Q1;
        shouldTerminate = false;
        thread animationThread(playAnimation);
        vector<BntStore> data = Q1.isBealConjectureSatisfied(1, 10, 3, 10, 5);
        this_thread::sleep_for(std::chrono::milliseconds(1800));
        cout << "-------Done!-------" << endl;
        
        shouldTerminate = true;
        animationThread.join();
        
        QuestionPrinter(data);
        cout << "Solution to Question 1" << endl;
    }
    void Question2()
    {
        BealConjecture01 Q1;
        shouldTerminate = false;
        thread animationThread(playAnimation);
        vector<BntStore> data = Q1.isBealConjectureSatisfied(1, 20, 3, 20, 5);
        this_thread::sleep_for(std::chrono::milliseconds(1800));
        cout << "-------Done!-------" << endl;
        shouldTerminate = true;
        animationThread.join();
        
        QuestionPrinter(data);
        cout << "Solution to Question 2" << endl;
    }
    void Question3()
    {
        BealConjecture02 Q1;
        shouldTerminate = false;
        thread animationThread(playAnimation);
        vector<BntStore> data = Q1.isBealConjectureSatisfied(3, 21, 3, 16, 0);
        cout << "-------Done!-------" << endl;
        shouldTerminate = true;
        animationThread.join();
        
        QuestionPrinter(data);
        cout << "Solution to Question 3" << endl;
    }
    void Question5()
    {
        BealConjecture03 Q1;
        shouldTerminate = false;
        thread animationThread(playAnimation);
        vector<BntStore> data = Q1.isBealConjectureSatisfied(1, 10, 3, 10, 10);
        this_thread::sleep_for(std::chrono::milliseconds(1800));
        cout << "-------Done!-------" << endl;
        shouldTerminate = true;
        animationThread.join();
        QuestionPrinter(data);
        cout << "Solution to Question 5" << endl;
    }
    void Question6()
    {
        
        BealConjecture05 Q1;
        system("cls");
        cout << "-------Done!-------" << endl;
        cout << "Solution to Question 6" << endl;
        Q1.findSquare();
    } 
    void Question7()
    {
        BealConjecture04 Q1;
        shouldTerminate = false;
        string input;
        cout << "Please enter two numbers separated by a comma.(e.g.10,50)";     

            cin >> input;
            int num1, num2;
            char comma;
            stringstream ss(input);
            if (ss >> num1 >> comma && comma == ',' && ss >> num2)
            {
                thread animationThread(playAnimation);
                Q1.isBealConjectureSatisfied01(1, 30, 3, 30, num1, num2, 5);
                shouldTerminate = true;
                animationThread.join();
            }
            else
            {
                cout << "Invalid input format." << endl;

            }

    }
    void Question8()
    {

        BealConjecture05 Q1;
        system("cls");
        cout << "-------Done!-------" << endl;
        Q1.findHighestBnt();
    }

    void solveProblem(int problemNumber) {
        switch (problemNumber) {
        case 1:

            
            Question1();
            break;
        case 2:

            
            Question2();
            break;
        case 3:

          
            Question3();
            break;
        case 5:

            
            Question5();
            break;
        case 6:

            Question6();
            break;
        case 7:

            
            Question7();
            break;
       
        case 8:

            
            Question8();
            break;

        default:
            std::cout << "Invalid problem number." << std::endl;
        }
    }

};





int main() 
{
    ProblemSolver solver;
    while (true) {
        cout << "Enter a Question number (or 0 to exit): ";
        MyData data;
        cin >> data;

        if (data.value == 0) {
            break;
        }
        solver.solveProblem(data.value);
    }

    return 0;
}