#include<iostream>
#include<unordered_map>
#include<map>
#include<vector>
#include<algorithm>
#include <fstream>
#include <sstream>
#include<string>
using namespace std;

// helper function use in subtract of two polynomails
void help_subtraction_poly(map<vector<int>,int>&p1,map<vector<int>,int>p2){
    for(auto i:p2){
        if(p1.find(i.first)!=p1.end())
            {p1[i.first]-=i.second;}
            else{
                p1[i.first]=-i.second;
            }
    }
   
}
// helper function use in addition of two polynomails
void help_addition_poly(map<vector<int>,int>&p1,map<vector<int>,int>p2){
    for(auto i:p2){
        if(p1.find(i.first)!=p1.end())
            {p1[i.first]+=i.second;}
            else{
                p1[i.first]=i.second;
            }
    }
}

// function to substract two polynomials with desiable coefficients
map<vector<int>,int> subtraction_poly(map<vector<int>,int>p1,map<vector<int>,int>p2,float n1=1,float n2=1){
    map<vector<int>,int> ans;
    if(n1==1) ans=p1;
    else{
    for(int i=0; i<n1; i++){
        help_addition_poly(ans,p1);
    }
    }
    for(int i=0; i<n2; i++){
        help_subtraction_poly(ans,p2);
    }
    return ans;
}

// function to add two polynomials with desiable coefficients
map<vector<int>,int> addition_poly(map<vector<int>,int>p1,map<vector<int>,int>p2,float n1=1,float n2=1){
    map<vector<int>,int> ans;
    if(n1==1) ans=p1;
    else{
    for(int i=0; i<n1; i++){
        help_addition_poly(ans,p1);
    }
    }
    for(int i=0; i<n2; i++){
        help_addition_poly(ans,p2);
    }
    return ans;
}

// function to write a monomial 
string createMonomial(const vector<int>& degrees) {
    string monomial = "";
    for (size_t i = 0; i < degrees.size(); ++i) {
        int degree = degrees[i];
        
        if (degree > 0) {
            if (!monomial.empty()) {
                monomial += "*";
            }
            
            monomial += "x" + to_string(i + 1);
            if (degree > 1) {
                monomial += "^" + to_string(degree);
            }
        }
    }
    return monomial.empty() ? "1" : monomial;
}

// function to print  a polynomial
string print_poly(const map<vector<int>, int>& p) {
    string polynomial = "";

    for (auto m = p.rbegin(); m != p.rend(); ++m) {
        int coeff = m->second;
        if (coeff == 0) continue;

        string term = createMonomial(m->first);

        // Handling the first term separately to avoid leading "+" for positive terms
        if (polynomial.empty()) {
            if (coeff == -1 && term != "1") {
                polynomial += "-";
            } else if (coeff != 1 || term == "1") {
                polynomial += to_string(coeff);
            }
            if (coeff != 1 && coeff != -1 || term == "1") {
                if (term != "1") polynomial += "*";
            }
            polynomial += term;
        } else {
            if (coeff < 0) {
                polynomial += " - ";
                if (coeff < -1 || term == "1") {
                    polynomial += to_string(-coeff);
                }
            } else {
                polynomial += " + ";
                if (coeff > 1 || term == "1") {
                    polynomial += to_string(coeff);
                }
            }
            if ((coeff > 1 || coeff < -1 || term == "1") && term != "1") {
                polynomial += "*";
            }
            polynomial += term;
        }
    }

    cout << polynomial << endl;
    return polynomial;
}

// function to check weather a polynomial is symmetric or not
bool isSymmetricPolynomial(const map<vector<int>, int>& polynomial) {
    for (const auto& term : polynomial) {
        const vector<int>& degrees = term.first;
        int coeff = term.second;

        // Generate all permutations of the degree vector
        vector<int> permutedDegrees = degrees;
        do {
            // Check if the polynomial has the same coefficient for this permutation
            if (polynomial.find(permutedDegrees) != polynomial.end() && polynomial.at(permutedDegrees) != coeff) {
                return false;
            }
        } while (next_permutation(permutedDegrees.begin(), permutedDegrees.end()));
    }
    return true;
}



// create  a class tableau to perform the operations of tableaux
class Tableau{
    private:
    vector<vector<int>> T;
    // recusion function to help to gentrate schur polynomial of a given shape tableau 
    void rec_function(int row,int col, Tableau U,int vari,int count,int degree,vector<int>&v,vector<vector<int>>& temp){
        if(count>=degree){
            
            temp.push_back(v);
            return;
        }
        int x;
        if(row==0 && col==0){x=1;}
        else if(row==0 && col!=0){x=T[row][col-1];}
        else if(row!=0 && col==0){x=T[row-1][col]+1;}
        else x=max(T[row-1][col]+1,T[row][col-1]);
        
        for(int i=x; i<=U.T[row][col]; i++){
            T[row][col]=i;
            v[i-1]++;
            
            if(col!=T[row].size()-1)rec_function(row,col+1,U,vari,count+1,degree,v,temp);
            else { rec_function(row+1,0,U,vari,count+1,degree,v,temp);}
            v[i-1]--;
        }
    }

     // function to get all the inside corner of  skew tableau
     // to show empty box we use zero
    vector<pair<int,int>> inner_corner(){
        vector<pair<int,int>> v;
        for(int i=0; i<T.size(); i++){
            if(T[i][0]!=0){
                break;
            }
            for(int j=0; j<T[i].size(); j++){
                if(T[i][j]==0){
                    v.push_back(make_pair(i,j));
                }
                else break;
            }
        }
        return v;
    }
// make a skew tableau with inserting a rectangle of empty box(zeros) of size no.of column of T and no. of rows of tableau U
    void insertRectangleAndMergeTableaux(Tableau U){
        Tableau R(T);
        
        int n=R.T[0].size();
        int m=U.T.size();
        T.clear();
       
        for(int i=0; i<m; i++){
            vector<int> v;
            for(int j=0; j<n+U.T[i].size(); j++){
                    if(j<n){
                        v.push_back(0);

                    }
                    else v.push_back(U.T[i][j-n]);
            }
            T.push_back(v);
        }
        for(int i=0; i<R.T.size(); i++){
        T.push_back(R.T[i]); 
        }
    }
    // function to that index is outside corner or not
    bool check_outside_corner(int x,int y){
        // if box in the last row
        if(x==T.size()-1 && T[x].size()-1==y){
            return true;
        }
        if(x==T.size()-1 && T[x].size()-1<y){
            return false;
        }
        // if box in the mid
        if(T[x].size()-1==y && T[x+1].size()-1<y){
            return true;
        }
        return false;
    }
    map<vector<int>,int> map_poly(vector<vector<int>>m){
        map<vector<int>,int> p;
        for(auto i: m){
            p[i]++;
        }
        return p;
    }


    public:
    // Default constructor
    Tableau(){}
    // Constructor to initialize from a 2D vector
    Tableau(const vector<vector<int>>& initial_data) : T(initial_data) {}

    // Constructor for 2D array
    template <size_t rows, size_t cols>
    Tableau(int (&initial_data)[rows][cols]) {
        T.resize(rows);
        for (size_t i = 0; i < rows; ++i) {
            T[i].assign(initial_data[i], initial_data[i] + cols);
        }
    }

    // Constructor to initialize from a string(row word) representation of the tableau
    Tableau(const string& word){
        vector<int> v;
    int n=word.size();
    v.push_back(word[n-1]-'0');
    for(int i=word.size()-2; i>=0; i--){
            if((word[i]-'0')<=(word[i+1]-'0')){
                
                v.push_back(word[i]-'0');
            }
            else {
                reverse(v.begin(),v.end());
                T.push_back(v);
                v.clear();
                v.push_back(word[i]-'0');
            }
    }
    
    
    reverse(v.begin(),v.end());
    T.push_back(v);
    v.clear();
    }

    // the function to print the tableau
    void printTableau() {
    for (const auto& row : T) {
        for (int elem : row) {
            cout << elem << " ";
            }
            cout << endl;
        }
        cout<<endl;
    }
// function  to read the tableau from a CSV file 
    bool readTableau(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            // print error if the is some issue with the file 
            cerr << "Error opening file: " << filename << endl;
            return false;
        }

        string line;
        while (getline(file, line)) {
            vector<int> row;
            stringstream ss(line);
            string value;
            while (getline(ss, value, ',')) {
                try {
                    row.push_back(stoi(value)); // Convert to integer and add to row
                } catch (const invalid_argument& e) {
                    cerr << "Invalid integer value in CSV: " << value << endl;
                    file.close();
                    return false;
                }
            }
            T.push_back(row); // Add the row to the 2D vector
        }

        file.close();
        return true;
    }   

    // function to check tableau is valid or not
    /*
        if the elements of tableau are weakly increasing in row and
        strictly increasing in column then the tableau is valid
    */

    bool isValid(){
        for(int i=0; i<T.size(); i++){
            for(int j=0; j<T[i].size(); j++){
                
                if(i==0 && j==0) continue; // if first element we continue
                if(i==0 ){
                    if( T[i][j]<T[i][j-1] ) return false; // check the firsr row
                    else continue;
                }
                if(j==0 ){
                    if( T[i][j]<=T[i-1][j]) return false; // check the first column
                    else continue;
                }
                if(T[i][j]<T[i][j-1] || T[i][j]<=T[i-1][j]) return false;   // check remaining elements
                
            }
            
        }
        return true;
    }

    // this function to row insertion
    void tableauInsertion( int x, int index=0) {
        if (index >= T.size()) {// If index exceeds size, create a new row and add x to it
            T.push_back({x});
           // print_tableau();
            return ;
        }

    
        // Find the position where x should be inserted
        auto it = upper_bound(T[index].begin(), T[index].end(), x);

        // If x should be appended to the end
        if (it == T[index].end()) {
            T[index].push_back(x);
           // print_tableau();
            
            return;
        }

        // Element to swap with x
        int temp = *it;
        *it = x;
       // print_tableau();
        // Recur to the next row
        tableauInsertion( temp, index + 1);
    }

    // function  reverse bumping to remove the element that insertion make new indexes
    void reverse_bumping(int x,int y){
        int val=T[x][y];
        auto it=T[x].begin()+y;
        
        T[x].erase(it);
        // printTableau();
        vector<int>::iterator low1;
        for(int i=x-1; i>=0; i--){
            
            low1=lower_bound(T[i].begin(),T[i].end(),val);
            y=low1-T[i].begin();
            if(y>0){y--;}
            
            int temp=T[i][y];
            T[i][y]=val;
            val=temp;
            // printTableau();
        }

    }


   
// function to make simple tableau from a skew tableau;
    void rectification(){

        int x,y;
        vector<pair<int,int>> v=inner_corner();
        // iterate the loop until all inner corner convert to outside corner
        while(v.size()!=0){
            x=v[v.size()-1].first;
            y=v[v.size()-1].second;
            v.pop_back();
        // iterate it until the inner corner trun into a outside corner
            while(!check_outside_corner(x,y)){
                //printTableau();

                // move the empty box right ward when there no box under this box or right is smaller then down box
                if(((x==T.size()-1 || T[x+1].size()-1<y)|| (T[x][y+1]<T[x+1][y])) && y<(T[x].size()-1)  ){
                    T[x][y]=T[x][y+1];
                    T[x][y+1]=0;
                    y++;
                
                    
                }
                // move the empty box downward when no box in right direction or down is smaller or equal to right
                
                else{
                    T[x][y]=T[x+1][y];
                    T[x+1][y]=0;
                    x++;
                    
                }
            }
            
            auto it=T[x].begin()+y;
            // erase the empty outside corner;
            T[x].erase(it);
            // erase the row if the row become empty
            if(T[x].size()==0){
                auto it1=T.begin()+x;
                T.erase(it1);
            }
           // printTableau();
        }

    }


    

// multipication of tableaus using row insertion 
/*
we inseat all the elements of tableau U into T from left to right and bottom to top
*/
    void row_insertion_multiplication(Tableau& U){
        for(int i=U.T.size()-1; i>=0; i--){
            for(int j=0; j<U.T[i].size(); j++){
                tableauInsertion(U.T[i][j]);
            }
        }
        //printTableau(); 
    }

// multipication of tableaus using sliding 
/* 
add a rectangle of size no. of column of T and no. of row in U and put T below the rectangle and
 U in right side of rectangle and perfom rectifiction of the new tableau
*/
    void rectification_multiplication(Tableau U){
            insertRectangleAndMergeTableaux(U);
            //printTableau();
            rectification();
            

    }

// function to create row string from a tableau
// read the tableau left to right and bottom to top
    string row_word(){
        string word="";
        for(int i=T.size()-1; i>=0; i--){
            for(int j=0; j<T[i].size(); j++){
                word+=(T[i][j]+'0');
            }
        }
       return word;
    }

// function to create colummn word from a tableau
// read the tableau bottom to top and left to right
    string col_word(){
        string word="";
        for(int i=0; i<T[0].size(); i++){
            for(int j=T.size()-1; j>=0; j--){
                if(i<T[j].size()) word+=(T[j][i]+'0');
            }
        }
        return word;
    }

// function to print the shape of a tableau
    vector<int> shape(){
        vector<int> ans;
        for(int i=0; i<T.size(); i++){
            ans.push_back(T[i].size());
        }
        
        if(ans.size()==0) return {0};
        return ans;
    }


// function to erase the values of tableau
    void erase(){
        // int n=T.size();
        // for(int i=n-1; i>=0; i--){
        //     T[i].clear();
        // }
        T.clear();
    }
// function to create a schur polynomial crrosponding to a given shape of a tableau and given number of variables
    map<vector<int>,int> schur_polynomial(int variables){
        int degree=0;
        for(int i=0; i<T.size(); i++){
            degree+=T[i].size();
        }
        Tableau U=T;
        for(int i=U.T.size()-1; i>=0; i--){
            for(int j=0; j<U.T[i].size(); j++){
                if(i==U.T.size()-1){ U.T[i][j]=variables; continue;}
                if(j>=U.T[i+1].size()){U.T[i][j]=variables; continue;}
                U.T[i][j]=U.T[i+1][j]-1;
            }
        }
        vector<int>v(variables,0);
        vector<vector<int>> temp;
        rec_function(0,0,U,variables,0,degree,v,temp);
        map<vector<int>,int>m=map_poly(temp);
        //print_poly(m);
        return m;
    
    }
};



    // Function to read multiple tableaux from a file
    static vector<Tableau> readMultipleTableau(const string& filename) {
        ifstream infile(filename);
        if (!infile) {
            cerr << "Error opening file." << endl;
            return {};
        }

        vector<Tableau> tableaux;
        vector<vector<int>> currentMatrix;
        string line;

        while (getline(infile, line)) {
            if (line.empty()) {
                if (!currentMatrix.empty()) {
                    tableaux.emplace_back(currentMatrix);
                    currentMatrix.clear();
                }
            } else {
                vector<int> row;
                stringstream ss(line);
                string item;

                while (getline(ss, item, ',')) {
                    row.push_back(stoi(item));
                }

                currentMatrix.push_back(row);
            }
        }

        if (!currentMatrix.empty()) {
            tableaux.emplace_back(currentMatrix);
        }

        return tableaux;
    }


    





