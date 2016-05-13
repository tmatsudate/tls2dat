//
//  ana.cpp
//  
//
//  Created by Takuya Matsudate on 2016/01/30.
//
//

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TFile.h>
#include <TTree.h>
#include <TH2.h>
#include <TMath.h>
using namespace std;

int main(int argc,char *argv[]){
    
    if ( argc < 2 ) {
        cout << "usage: ./anatls [data filename] \n" << endl;
        return 0;
    }
    
    string input=argv[1];
    string output=argv[1];
    output+=".dat";

    long ntot=0,ndead=0,npass=0,nspot=0;
    
    std::string::size_type flag;
    string a,b,c,d;
    stringstream ids;
    ifstream data(input.c_str());
    //ofstream ofs();
    ofstream ofs(output.c_str());
    
    while (getline(data,a))
    {
        flag = a.find("Tracking particle number");
        if (flag != std::string::npos)
        {
            ntot++;                                  //sum up total particle number.
            for(int i=0;i<2;i++) getline(data,a);    //To cut header lines.
            
            
            while (getline(data,a))
            {
                flag = a.find("Termination status of particle number"); //make output file.
                if (flag != std::string::npos) 
		{
		  ofs << " -1 -1 -1 -1 -1 -1 -1 -1 -1" << endl;
		  break;
		}
                else ofs << a.c_str() << endl;
            }
            
        }
        
        flag = a.find("Point inside E mesh material region");
        if (flag != std::string::npos) ndead++;
        
        flag = a.find("Point inside E mesh material region  12");
        if (flag != std::string::npos) npass++;
	
	flag = a.find("Point inside E mesh material region  13");
        if (flag != std::string::npos) nspot++;
        
    }
    data.close();
    ofs.close();
    
    int v;
    cout << v << endl;
    
    cout << input.c_str() << " " << ntot << " " << ndead << " " << npass << " " << nspot  << endl;
    //cout << "col " << ndead << endl;
    //cout << "pass " << npass << endl;
    
    return 0;
}
