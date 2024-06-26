const solution = require('./solution');

describe('solution function: A - B', () => {
    test('subtract 3 - 2 to equal 1', () => {
        const result = solution(3, 2);
        expect(result).toBe(1);
    });

    test('subtract 1 - 5 to equal -4', () => {
        const result = solution(1, 5);
        expect(result).toBe(-4);
    });
});