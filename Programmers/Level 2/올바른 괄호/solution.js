const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let s = null;

class Stack {
    constructor() {
        this._arr = [];
    }

    push(item) {
        this._arr.push(item);
    }

    pop() {
        return this._arr.pop();
    }

    peak() {
        return this._arr[this._arr.length - 1];
    }

    empty() {
        return this._arr.length === 0;
    }
}

const solution = (s) => {
    let st = new Stack();
    let correct = true;

    // 여는 괄호만 스택에 넣을 거임
    for (let i = 0; i < s.length; i++) {
        if (s[i] === '(') {
            st.push(s[i]);
        } else {
            if (!st.empty() && st.peak() === '(') {
                st.pop();
            } else {
                correct = false;
                break;
            }
        }
    }

    if (!st.empty()) correct = false;
    return correct;
}

rl.on('line', (line) => {
    s = line;
    rl.close();
}).on('close', () => {
    const res = solution(s);
    console.log(res);
    process.exit();
});