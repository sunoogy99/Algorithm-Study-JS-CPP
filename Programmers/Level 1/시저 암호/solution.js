const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let s = null;
let n = null;

const solution = (s, n) => {
    return s.split('').map(e => {
        let ret = e.charCodeAt() === 32 ? 32 : e.charCodeAt() + n; // space 거르기
        
        // z에서 넘어간 경우
        if (e.charCodeAt() >= 'a'.charCodeAt() && e.charCodeAt() <= 'z'.charCodeAt()) {
            if (ret > 'z'.charCodeAt()) {
                ret -= ('z'.charCodeAt() - 'a'.charCodeAt() + 1);
            } 
        }
        else if (e.charCodeAt() >= 'A'.charCodeAt() && e.charCodeAt() <= 'Z'.charCodeAt()) {
            if (ret > 'Z'.charCodeAt()) {
                ret -= ('Z'.charCodeAt() - 'A'.charCodeAt() + 1);
            }
        }
        
        return String.fromCharCode(ret);
    }).join('');
}

rl.on('line', (line) => {
    if (!s) {
        s = line;
    }
    else if (!n) {
        n = +line;
    }

    if (s && n) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(s, n);
    console.log(res);
    process.exit();
});