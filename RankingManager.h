#pragma once
#include <vector>
using namespace std;

class RankingManager
{
private:
    vector<int> rankings;
    const char* fileName;
    const int RANK_SIZE = 10;
public:
    // 저장 파일명 설정 생성자
    RankingManager(const char* fileName = "rank.txt");

    // 파일에서 랭킹 데이터 로드 및 정렬
    void load();
    // 새로운 기록을 리스트에 추가 후 파일 덮어쓰기 저장
    void saveScore(int score);
    // 현재 저장된 랭킹 목록 반환
    const vector<int>& getRank() const;
};