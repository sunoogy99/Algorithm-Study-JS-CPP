const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let T = null;
let count = 0;
let ps = [];

class Stack {
    constructor() {
        this._arr = [];
    }

    push(data) {
        this._arr.push(data);
    }

    pop() {
        return this._arr.pop();
    }

    isEmpty() {
        return this._arr.length === 0;
    }

    top() {
        if (this.isEmpty()) return -1;
        return this._arr[this._arr.length - 1];
    }
}

const solution = (ps) => {
    let st = new Stack();
    let retMsg = 'YES';

    for (let i = 0; i < ps.length; i++) {
        // 여는 괄호만 스택에 넣을 거임
        if (ps[i] === '(') {
            st.push(ps[i]);
        } else {
            if (st.isEmpty()) {
                retMsg = 'NO';
                break;
            } else {
                st.pop();
            }
        }
    }

    if (!st.isEmpty()) {
        retMsg = 'NO';
    }

    return retMsg;
}

rl.on('line', (line) => {
    if (!T) {
        T = +line;
    } else {
        ps = line.split('');
        count++;
        const res = solution(ps);
        console.log(res);
        ps = [];
    }

    if (count === T) {
        rl.close();
    }
}).on('close', () => {
    process.exit();
});