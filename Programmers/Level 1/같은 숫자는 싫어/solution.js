const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

class Stack {
    constructor() {
        this._arr = [];
    }

    push(item) {
        this._arr.push(item);
    }

    // pop() {
    //     return this._arr.pop();
    // }

    // 스택 최상단에 있는 값 조사
    peak() {
        return this._arr[this._arr.length - 1];
    }

    empty() {
        return this._arr.length === 0;
    }
}


const solution = (arr) => {
    let st = new Stack();
    let res = [];
    
    arr.map(e => {
        if (st.empty()) {
            st.push(e);
            res.push(e);
        }
        else {
            if (st.peak() !== e) {
                // st.pop()을 넣은 이유는 불필요한 메모리 낭비 줄이려고 넣은 건데..!
                // st.pop();
                st.push(e);
                res.push(e);
            }
        }
    });
    
    return res;
}

let arr = null;

rl.on('line', (line) => {
    arr = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(arr);
    console.log(res);
    process.exit();
});