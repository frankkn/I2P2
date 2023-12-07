#define MAX_N 1000
#define MAX_Bit 5
#define MAX 100000

istream& operator>>(istream &in, BigInt &b)
{
    string ch;
    in >> ch;
    if (ch[0] == '-')
        ch = ch.substr(1, ch.length() - 1), b.sign = -1; // substr(起始位置, 長度)，去掉負號
    else
        b.sign = 1;
    reverse(ch.begin(), ch.end()); // 反轉，為了從後面開始存
    int id = 0;
    for (int i = 0; i < ch.length(); i += MAX_Bit)
    {
        string sub = ch.substr(i, MAX_Bit);
        reverse(sub.begin(), sub.end()); 
        b[id++] = stoi(sub);
    }
    b.l = id; // 紀錄m的長度
    return in;
}
ostream &operator<<(ostream &out, BigInt b)
{
    out << ((b.sign == -1) ? "-" : "");
    out << b.m[b.l - 1]; // 最左邊的數字不用補0
    for (int i = b.l - 2; i >= 0; i--)
    {
        out.width(MAX_Bit); // 補滿5位數
        out.fill('0'); // 補0
        out << b[i];
    }
    return out;
}
BigInt BigInt::operator+(const BigInt &y)
{
    BigInt x(*this); // 複製一份
    int i;
    long long h;
    for (h = 0, i = 0; i < x.l || i < y.l || h; i++)
    {
        h += (i < x.l) * x[i] * x.sign + (i < y.l) * y[i] * y.sign; // 加法運算
        x[i] = h % MAX;
        h /= MAX;
    }
    
    x.l = i;
    for (; x.l > 1 && !x[x.l - 1]; x.l--); // 去掉前面的0
    x.sign = (x[x.l - 1] >= 0 ? 1 : -1); // 紀錄正負號
    
    if (x[x.l - 1] >= 0) // 開頭是正的
    {
        for (i = 0; i < x.l; i++) // 檢查是否有進位
            if (x[i] < 0) // 有進位
                x[i + 1]--, x[i] += MAX; // 進位
    }
    else // 開頭是負的
    {
        for (i = 0; i < x.l; i++)
            if (x[i] > 0)
                x[i + 1]++, x[i] -= MAX; 
    }

    for (i = 0; i < x.l; i++) // 將結果乘上正負號，保持陣列內的數字都是正的
        x[i] *= x.sign;
    
    for (; x.l > 1 && !x[x.l - 1]; x.l--); // 去掉前面的0
    
    if (x.sign == -1 && x.l == 1 && x[0] == 0) // 最後做等於0的特判，如果是0將sign改為1
        x.sign = 1;
    return x;
}
BigInt BigInt::operator-(const BigInt &y)
{
    BigInt yy(y);
    yy.sign *= -1;
    return *this + yy;
}