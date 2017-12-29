#include <iostream>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

//Functions for option 1
int calculateHamming();
int calculateOutputSize(const string &);
string calculateHammingCode(int, const string &);


//Common to both options
bool isValidate(string);

//Functions for option 2
int findErrorsHamming();
int calculateInputSize(const string &);
string findCorrectHammingCode(const string &);


int main() 
{
   char choice;
   cout << "---------------HAMMING CODE---------------" << endl;
   cout << "Select an Option. " <<endl;
   cout << "1. Calculate Hamming Code from Input Data Stream. " << endl;
   cout << "2. Find error in a Hamming Code given as Input. " << endl;
   cout << "\n------NOTE: For Option 2, Hamming Code CAN DETECT & CORRECT ONLY A SINGLE BIT ERROR----" << endl;
   cout << "--- Select either 1 or 2 : ";
   cin >> choice;
   switch(choice)
   {
       case '1':
            return calculateHamming();
           
       case '2':
            return findErrorsHamming();
            
       default:
            cout << "Invalid Choice Entered. " << endl;
            return -1;
   }
   return 0;
}


//------------Functions for Option 1-------------------
int calculateHamming()
{
    string input;
    int outputsize;
 
    cout << "Enter any input data : ";
    cin >> input;
 
    if (isValidate(input))
    {
         cout << "It is a Valid String." << endl;
 
         outputsize = calculateOutputSize(input);
         cout << "Total Output size : " << outputsize;
 
         string output = calculateHammingCode(outputsize, input);
         cout << "The Hamming Code is : " << output;         
    }
    else
    {
         cout << "Invalid Input. Process terminating..." << endl;
         return -1;
    }
    return 0;
}






int calculateOutputSize(const string &str)
{
    int n = str.size();
    //cout << "The size of the string : " << n;
    for (int i = 0; ;++i)
    {
        if (pow(2, i) >= (n + i + 1))
            return (i + n);
    }
    return 0;
}


string calculateHammingCode(int n, const string &str)
{
    string output(n, '-');
    
    auto it = str.begin();
    int k = n - str.size();


    //Find the output string with input data entered without Parity bits
    for (int position = 0, index = 0; it != str.end(); ++position)
    {
        if (pow (2, index) == (position + 1))
        {
            ++index;
            continue;
        }
        output[position] = *it++;
    }
    cout << endl;
    cout << "Output(Without Parity Bits) : " << output << endl;


    //Find the output string now with Parity bits
    bitset<10> bits;
    for (int index = 0; index < k; ++index)
    {
        int positionofparity = 0;
        int countof1s = 0;
        for (size_t c = 1; c <= output.size(); ++c) //1 - outputsize()
        {
                bits = c;
                if (bits.test(index)) // index from 0 to 3
                {
                    if (output[c - 1] == '-')
                        positionofparity = c - 1;
                    else if (output[c - 1] == '1')
                        ++countof1s;
                }
        }   
        if (countof1s % 2 != 0)
            output[positionofparity] = '1';
        else
            output[positionofparity] = '0';
    }
    cout << "Output : " << output << endl;
    return output;    
}
//------------End of Functions for Option 1-------------------


//------------Functions common for both-------------------
bool isValidate(string str)
{
    auto it = str.begin();
    int index = 0;
    for (it = str.begin(); it != str.end(); ++it, ++index)
    {
       if (!(*it == '0' || *it == '1'))
        return false;
       
    }
    return true;
    
}
//------------End of Functions common for both-------------------


//------------Functions for Option 2-------------------
int findErrorsHamming()
{
    string hammingcode;
   
    cout << "Enter the hamming code : ";
    cin >> hammingcode;
    
    if (isValidate(hammingcode) && hammingcode.size() > 4)
    {
        cout << "It is a Valid String." << endl;
 
        string correcthammingcode;
        correcthammingcode = findCorrectHammingCode(hammingcode);
        if (correcthammingcode == hammingcode)
            cout << "Input does not have any errors. " << endl;
        else
        {
            cout << "Correct Hamming Code : " << correcthammingcode << endl;
            if (correcthammingcode.size() == hammingcode.size())
            {
                cout << "Error(s) at positions : ";
                for (size_t index = 0; index != hammingcode.size(); ++index)
                {
                    if (correcthammingcode[index] != hammingcode[index])
                        cout << " " << index + 1;
                }
            }
            else
                cout << "You've entered an invalid stream of data." << endl;
        }
    }
    else
    {
         cout << "Invalid Input. Process terminating..." << endl;
         return -1;
    }
    return 0;
}


int calculateInputSize(const string &hammingcode)
{
    size_t hammingcodesize = hammingcode.size();
    int k;
    for (k = 0; pow(2, k) < hammingcodesize; ++k)
        ;
    return hammingcodesize - k;
}

string findCorrectHammingCode(const string &hammingcode)
{
    bitset<10> output (0);
    bitset<10> bits (0);
    size_t k = hammingcode.size() - calculateInputSize(hammingcode);
    bool errorhasoccured = false;
    for (size_t c = 0; c < k; ++c)
    {
        int countof1s = 0;
        for (size_t index = 1; index <= hammingcode.size(); ++index)
        {
            bits = index;
            if (bits.test(c))
            {
                if (hammingcode[index - 1] == '1')
                    ++countof1s;
            }
            // if (!(pow(2, power) == (index + 1)))
            //     input += ch;
            // else
            //     ++power;
            // index++;
        }
        if (countof1s % 2 != 0)
        {
            output.set(c, 1);
            errorhasoccured = true;
        }
    }
    if (errorhasoccured)
    {
        unsigned int finalindex = (unsigned int) output.to_ulong();
        string outputstring = hammingcode;
        outputstring[finalindex - 1] = outputstring[finalindex - 1] == '1' ? '0' : '1';
        return outputstring;
    }
    else
        return hammingcode;
    
    // cout << "Input String : " << input;
    // string correcthammingcodeintermediate = calculateHammingCode(hammingcode.size(), input);
    // if (correcthammingcodeintermediate.size() == hammingcode.size())
    //    for (size_t index = 0, error = 0; index != hammingcode.size() && error < 2; index = )
    //         indexerror[error++] = index;     
    
}


bool isValidMessageStream(const string &hammingcode)
{
    size_t codesize = hammingcode.size();
    for (size_t k = 1; k + 1 < codesize; ++k)
        if (pow(2, k) >= codesize + 1)
            return true;
    return false;        
}
//------------End of Functions for Option 2-------------------