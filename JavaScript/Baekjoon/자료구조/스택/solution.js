const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

class Stack {
    constructor() {
        this._arr = [];
    }

    push(data) {
        this._arr.push(data);
    }

    pop() {
        if (this.isEmpty()) return -1;
        return this._arr.pop();
    }

    isEmpty() {
        return this._arr.length === 0;
    }

    size() {
        return this._arr.length;
    }

    top() {
        if (this.isEmpty()) return -1;
        return this._arr[this._arr.length - 1];
    }
}

let N = null;
let count = 0;
const oper = [];

const solution = (oper) => {
    const st = new Stack();
    const res = [];

    for (let op of oper) {
        switch (op[0]) {
            case 'push':
                let num = +op[1];
                st.push(num);
                break;
            case 'pop':
                res.push(st.pop());
                break;
            case 'size':
                res.push(st.size());
                break;
            case 'empty':
                res.push(st.isEmpty() ? 1 : 0);
                break;
            case 'top':
                res.push(st.top());
                break;
            default:
                break;
        }
    }

    return res.join('\n');
}

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    } else {
        oper.push(line.split(' '));
        count++;
    }

    if (count === N) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(oper);
    console.log(res);
    process.exit();
});