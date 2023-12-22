#define MAXB 5
#define MAX 100000

istream& operator>>(istream& in, BigInt& b) {
    string ch;
    cin >> ch;
    if (ch[0] == '-') {
        ch = ch.substr(1, ch.length() - 1);
        b.sign = -1;
    } else {
        b.sign = 1;
    }
    reverse(ch.begin(), ch.end());
    int id = 0;
    for (int i = 0; i < ch.length(); i += MAXB) {
        string sub = ch.substr(i, MAXB);
        reverse(sub.begin(), sub.end());
        b[id++] = stoi(sub);
    }
    b.l = id;
    return in;
}

ostream& operator<<(ostream& out, BigInt b) {
    out << (b.sign == -1 ? "-" : "");
    out << b[b.l - 1];
    for(int i = b.l-2; i >= 0; i--){
    	out.width(MAXB);
        out.fill('0');
    	out << b[i];
    }
    return out;
}

BigInt BigInt::operator+(const BigInt& y) {
    BigInt x(*this);
    int i;
    long long h;
    for(i = 0, h = 0; i < x.l || i < y.l || h; i++){
    	h += (i < x.l) * x[i] * x.sign + (i < y.l) * y[i] * y.sign;
        x[i] = h % MAX;
    	h /= MAX;
    }
    x.l = i;
    x.sign = (x[x.l-1] >= 0? 1:-1);
    for(; x.l > 1 && !x[x.l-1]; x.l--);
    if(x[x.l-1] >= 0){
    	for(i = 0; i < x.l; i++){
        	if(x[i] < 0){
            	x[i+1]--;
                x[i] += MAX;
            }
        }     
    }else{
        for(i = 0; i < x.l; i++){
        	if(x[i] > 0){
            	x[i+1]++;
                x[i] -= MAX;
            }
        } 
    }
    for(; x.l > 1 && !x[x.l-1]; x.l--);
    for(i = 0; i < x.l; i++) x[i] *= x.sign;
    if(x.sign == -1 && x[0] == 0 && x.l == 1)	x.sign = 1;
    return x;
}

BigInt BigInt::operator-(const BigInt& y) {
    BigInt yy(y);
    yy.sign *= -1;
    return *this+yy;
}
