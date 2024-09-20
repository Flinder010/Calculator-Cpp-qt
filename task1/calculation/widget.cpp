#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this -> setMaximumSize(230,330);
    this -> setMinimumSize(230,330);

    this -> setWindowTitle("计算器");

    QFont f("Times New Roma" , 14);    //显示屏字体以及大小
    ui -> mainLineEdit -> setFont(f);

    QIcon conbackspace("D:\\C++daima\\task1\\calculation\\backspace.png");  //撤销上放图片
    ui -> deleteButton -> setIcon(conbackspace);

    ui -> equalButton ->setStyleSheet("background:blue");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_oneButton_clicked()
{
    expression += "1";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_twoButton_clicked()
{
    expression += "2";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_threeButton_clicked()
{
    expression += "3";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_fourButton_clicked()
{
    expression += "4";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_fiveButton_clicked()
{
    expression += "5";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_sixButton_clicked()
{
    expression += "6";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_sevenButton_clicked()
{
    expression += "7";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_eighhtButton_clicked()
{
    expression += "8";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_nineButton_clicked()
{
    expression += "9";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_zeroButton_clicked()
{
    expression += "0";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_dotButton_clicked()
{
    expression += ".";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_modButton_clicked()
{
    expression += "%";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_plusButton_clicked()
{
    expression += "+";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_minusButton_clicked()
{
    expression += "-";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_divButton_clicked()
{
    expression += "/";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_multiButton_clicked()
{
    expression += "*";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_leftButton_clicked()
{
    expression += "(";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_rightButton_clicked()
{
    expression += ")";
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_factbutton_clicked()
{
    int cur[10000];
    cur[1] = 1;
    int digit = 1, carry = 0, res;
    QStack<char> s_sum, s_opt;
    QVector<int> s_num;     //储存数值
    QString result;

    char opt[128] = {0};
    int i = 0;
    int tmp = 0;
    bool correct = 1;

    QByteArray ba;
    ba.append( expression );  //将QString转化成QByteArray
    strcpy( opt, ba.data() ); //data函数把QByteArray转化成const char

    while( opt[i] != '\0' )
    {
        if( opt[i] >= '0' && opt[i] <= '9' )
        {
            tmp = tmp * 10 + opt[i] - '0';
            i++;
            if( tmp >= 3251 )
            {
                ui -> mainLineEdit -> setText( "Error" );
                expression.clear();
                correct = 0;
                break;
            }
        }
        else
        {
            ui -> mainLineEdit -> setText( "Error" );
            expression.clear();
            correct = 0;
            break;
        }
    }
    if( tmp == 1 )
    {
        ui -> mainLineEdit -> setText( "1" );
        expression.clear();
        correct = 0;
    }
    for( int i = 2; i <= tmp; i++ )
    {
        for( int j = 1; j <= digit; j++)
        {
            res = cur[j] * i + carry;
            cur[j] = res % 10;
            carry = res / 10;
        }while( carry )
        {
            digit++;
            cur[digit] = carry % 10;
            carry /= 10;
        }
    }
    for( int i = digit; i > 0; i-- )
    {
        result.append( QString::number( cur[i] ) );
    }
    if( correct == 1 )
    {
        ui -> mainLineEdit -> setText( result );
        expression.clear();
    }
}

void Widget::on_clearButton_clicked()
{
    expression.clear();
    ui -> mainLineEdit -> clear();
}

void Widget::on_deleteButton_clicked()
{
    expression.chop(1);
    ui -> mainLineEdit -> setText(expression);
}

void Widget::on_equalButton_clicked()
{
    QStack<char> s_sum,s_opt;
    QStack<double> s_num;     //储存数值

    char opt[128] = {0};
    int i = 0;
    double tmp = 0, num1, num2;

    QByteArray ba;
    ba.append(expression);  //将QString转化成QByteArray
    strcpy(opt, ba.data()); //data函数把QByteArray转化成const char

    while( opt[i] != '\0' || s_opt.empty() != true)
    {
        if(opt[i]>='0' && opt[i]<='9')
        {
            tmp = tmp * 10 + opt[i] - '0';
            i++;
            if( opt[i] < '0' || opt[i] > '9')
            {
                s_num.push( tmp );
                tmp = 0;
            }
        }
        else  //符号
        {
            if( ( opt[i] == '-' && i == 0 ) || ( i != 0 && opt[i] == '-' && ( opt[ i - 1 ] < '0' || opt[ i - 1 ] > '9' ) ) )
            {
                s_num.push( 0 );
            }
            if( s_opt.empty() == true || Priority( opt[i] ) > Priority( s_opt.top() ) || ( s_opt.top() == '(' && opt[i] != ')'))
            {
                s_opt.push( opt[i] );
                i++;
                continue;
            }

            if (s_opt.top() == '(' && opt[i] == ')' )
            {
                s_opt.pop();
                i++;
                continue;
            }

            if( Priority(opt[i]) <= Priority( s_opt.top()) || (opt[i] == ')' && s_opt.top() != '(') || (opt[i] == '\0' && s_opt.empty() != true))
            {
                char ch = s_opt.top();
                s_opt.pop();
                switch(ch)
                {
                    case '+':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push( num1 + num2 );
                        break;
                    case '-':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push( num2 - num1 );
                        break;
                    case '*':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push( num1 * num2 );
                        break;
                    case '/':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push( num2 / num1 );
                        break;
                    case '%':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push( int(num2) % int(num1) );
                        break;
                }
            }
        }
    }
    ui -> mainLineEdit -> setText( QString::number( s_num.top() ) );
    expression.clear();
}

int Widget::Priority(char ch){
    switch(ch)
    {
        case '(':
            return 3;
        case '*':
        case '%':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

void Widget::on_PFButton_clicked()
{
    QStack<char> s_sum, s_opt;
    QVector<int> s_num;     //储存数值
    QString result;

    char opt[128] = {0};
    int i = 0;
    int tmp = 0;
    bool correct = 1;

    QByteArray ba;
    ba.append( expression );  //将QString转化成QByteArray
    strcpy( opt, ba.data() ); //data函数把QByteArray转化成const char

    while( opt[i] != '\0' )
    {
        if( opt[i] >= '0' && opt[i] <= '9' )
        {
            tmp = tmp * 10 + opt[i] - '0';
            i++;
            if( tmp >= 1e9 )
            {
                ui -> mainLineEdit -> setText( "Error" );
                expression.clear();
                correct = 0;
                break;
            }
        }
        else
        {
            ui -> mainLineEdit -> setText( "Error" );
            expression.clear();
            correct = 0;
            break;
        }
    }
    for( int j = 2; j <= tmp; j++ )
    {
        if( tmp % j == 0)
        {
            tmp /= j;
            s_num.push_back( j );
            j--;
        }
    }
    if( correct == 1 )
    {
        for( int k = 0; k < s_num.size(); k++ )
        {
            result.append( QString::number( s_num[ k ] ) );
            if( k!= s_num.size() - 1 )
            {
               result.append( "*" );
            }
        }
        ui -> mainLineEdit -> setText( result );
        expression.clear();
    }
}
