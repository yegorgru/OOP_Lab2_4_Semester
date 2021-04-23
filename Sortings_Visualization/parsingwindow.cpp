#include "parsingwindow.h"
#include "ui_parsingwindow.h"
#include "parser.h"
#include <iostream>


using namespace std;


//queue<char> to_revpol(const QString &input);
//double calc(queue<char> in);
//void test(const string& input, int pos, int &complexity_quadr,int& complexity_log,int& temp_comp_quad );
ParsingWindow::ParsingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParsingWindow)
{
    ui->setupUi(this);
}

ParsingWindow::~ParsingWindow()
{
    delete ui;
}

void ParsingWindow::on_pushButton_clicked()
{
 Component *simple = new Leaf;
   std::cout << "Client: I've got a simple component:\n";
   Simple_tree(simple);
 //QString qstr = QString::fromStdString(Simple_tree(simple));

     // ui->theorComplexity->setText(qstr);
      std::cout << "\n\n";
      Component *tree = new Composite;
        Component *branch1 = new Composite;
        Component *leaf_1 = new Leaf;
          Component *leaf_2 = new Leaf;
          Component *leaf_3 = new Leaf;
          branch1->Add(leaf_1);
            branch1->Add(leaf_2);
            Component *branch2 = new Composite;
            branch2->Add(leaf_3);
            tree->Add(branch1);
            tree->Add(branch2);
            std::cout << "Client: Now I've got a composite tree:\n";
            Simple_tree(tree);
            std::cout << "\n\n";
            delete simple;
              delete tree;
              delete branch1;
              delete branch2;
              delete leaf_1;
              delete leaf_2;
              delete leaf_3;
//    QString input = ui->inputLine->text();
//    string in = input.toLocal8Bit().constData();
//    int pos = 0;
//    int complexity_quadr = 0;
//    int complexity_log = 0;
//    int temp_comp_quad = 0;
//    test(in,pos,complexity_quadr, complexity_log, temp_comp_quad);
// ui->theorComplexity->setText("О(n^"  + QString::number(complexity_quadr) + ") " + QString::number(complexity_log) );
}
//bool check_substr(string text,string substring){
//    int found = text.find(substring);
//    if (found != std::string::npos)
//    {
//        return true;
//    }
//    return false;
//}
//void test(const string& in, int pos, int &complexity_quadr, int& complexity_log,int& temp_complex_quad ) {

//    // string in = input.toLocal8Bit().constData();


//     if (pos == in.length()) {return;}



//     if(check_substr(in.substr(pos,in.length()),"loop")){
//        complexity_quadr++;
//    cout<<complexity_quadr << endl;
//     }
//     if (check_substr(in.substr(pos,in.length()),");")) {
//         temp_complex_quad = complexity_quadr;
//         complexity_quadr = 0;
//         if(check_substr(in.substr(pos,in.length()),"loop")){
//            complexity_quadr++;

//            //cout<<temp_complex_quad << endl;
//         }
//     }
//     if (check_substr(in.substr(pos,in.length()),"loop{n/2}")){

//        complexity_log = log(3);
//     }

//     for(int i= pos; i < in.length(); i++){
//        if(in[i] == '(' ) {
//            pos = i;
//            test(in, pos+1,complexity_quadr, complexity_log,temp_complex_quad);
//        }
//     }
//    if (temp_complex_quad > complexity_quadr) {
//        complexity_quadr = temp_complex_quad;
//     //cout<<complexity << endl;
//    }

//}



