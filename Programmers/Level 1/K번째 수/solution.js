// 입출력 문제로 solution 함수만 작성

const solution = (array, commands) => {
    let answer = [];
    for (let [i, j, k] of commands) {
        answer.push(array.slice(i - 1, j).sort((a, b) => a - b)[k - 1]);
    }
    return answer;
}