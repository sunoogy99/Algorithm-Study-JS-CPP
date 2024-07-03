// 입력 방식이 명확하지 않아 solution 함수만 작성

function solution(arr1, arr2) {
    let answer = [];
    
    arr1.forEach((e, i) => {
        let temp = [];
        e.forEach((_, j) => {
           temp.push(arr1[i][j] + arr2[i][j]); 
        });
        answer.push(temp);
    })
    return answer;
}