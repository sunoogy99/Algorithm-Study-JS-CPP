const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let arr = [];

const solution = (arr) => {
    // let temp = arr; -> 얕은 복사 : 객체 참조값 (주소값) 반환
    // 변경하면 arr 내용도 변경됨
    let temp = Array.from(arr).sort((a, b) => a - b);
    let minVal = temp[0];
    arr = arr.filter(e => e !== minVal);
    return arr.length === 0 ? [-1] : arr;
}

rl.on('line', (line) => {
    arr = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(arr);
    console.log(res);
    process.exit();
});