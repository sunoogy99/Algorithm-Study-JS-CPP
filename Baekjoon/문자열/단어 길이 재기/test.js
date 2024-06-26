const solution = require('./solution');

describe('solution function test: 단어 길이 재기', () => {
    test('test case: pulljima', () => {
        expect(solution('pulljima')).toBe(8);
    });
});