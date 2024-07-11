const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let s = null;

const solution = (s) => {
    let answer = [];
    
    // 해당 문자가 발견된 인덱스 관리 딕셔너리 key: a-z, value: -1
    let charIndex = {}; 
    Array.from(Array(26), (_, i) => i + 'a'.charCodeAt()).map(e => {
        return charIndex[String.fromCharCode(e)] = -1;
    });

    s.split('').map((c, i) => {
        // 문자가 아직 발견된 적 없는 경우
        if (charIndex[c] === -1) {
            answer.push(-1);
            charIndex[c] = i; // 문자 발견된 인덱스를 기록한다.
        }
        // 최근 문자 인덱스를 찾아서 거리를 구한다.
        else {
            answer.push(i - charIndex[c]);
            charIndex[c] = i; // 문자 발견된 인덱스를 기록한다.
        }
    });

    return answer;
}

rl.on('line', (line) => {
    s = line;
    rl.close();
}).on('close', () => {
    const res = solution(s);
    console.log(res);
    process.exit();
});