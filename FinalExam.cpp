#pragma comment(lib, "Opengl32.lib")
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#pragma once

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>
#include <vector>

class Object {
public:
    float x, y, width, height;

    Object(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height) {}

    virtual void OnCollisionEnter(Object& other) = 0;
};

class Star : public Object {
public:
    Star(float x, float y, float size)
        : Object(x, y, size, size) {}

    void Draw() {
        glColor3f(1.0f, 1.0f, 1.0f);  // White color for stars
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
    }

    void Update(float scrollSpeed) {
        x -= scrollSpeed;
        if (x < -1.5f) {
            x = 1.5f;  // Reset position when star goes offscreen
            y = (float(rand()) / RAND_MAX) * 2.0f - 1.0f;  // Randomize y position
        }
    }

    void OnCollisionEnter(Object& other) override {
        // Stars do not have collision logic, so leave this empty
    }
};

class Player : public Object {
public:
    float velocityY;
    bool isJumping;
    float rotation;
    float groundLevel;
    float jumpForce;
    float rotationSpeed;

    Player(float x, float y, float size, float groundLevel)
        : Object(x, y, size, size), velocityY(0), isJumping(false), rotation(0), groundLevel(groundLevel),
        jumpForce(0.25f), rotationSpeed(5.0f) {}

    void OnCollisionEnter(Object& other) override {
        // Implement collision logic for Player
    }

    void Jump() {
        if (!isJumping) {
            velocityY = jumpForce;
            isJumping = true;
        }
    }

    void ApplyGravity(float gravity) {
        if (y > groundLevel || velocityY > 0) {  // 공중에 있거나 점프 중
            velocityY -= gravity;
            y += velocityY;
            if (isJumping) {
                RotatePlayer();  // 회전 적용
            }
        }
        else {  // 땅에 닿은 경우
            y = groundLevel;
            velocityY = 0;
            isJumping = false;
            rotation = 0;  // 점프가 끝나면 회전 각도 초기화
        }
    }

    void RotatePlayer() {
        rotation -= rotationSpeed;  // 시계 방향 회전 속도로 변경
        if (rotation <= -360.0f) {
            rotation += 360.0f;
        }
    }
};

Player player(-0.85f, -0.15f, 0.3f, -0.5f);  // 초기 위치와 땅 레벨 조정

float gravity = 0.01f;    // 중력 가속도
bool isJumpKeyPressed = false;
auto lastJumpTime = std::chrono::high_resolution_clock::now();

class Obstacle : public Object {
public:
    Obstacle(float x, float y, float width, float height)
        : Object(x, y, width, height) {}

    void Draw() {
        glColor3f(0.0f, 1.0f, 0.0f);  // 초록색
        glBegin(GL_QUADS);
        glVertex2f(x - width / 2, y - height / 2);
        glVertex2f(x + width / 2, y - height / 2);
        glVertex2f(x + width / 2, y + height / 2);
        glVertex2f(x - width / 2, y + height / 2);
        glEnd();
    }

    void Update() {
        x -= 0.01f;  // 장애물 이동 속도
        if (x < -1.5f) {
            x = 1.5f;  // 화면을 벗어나면 다시 나타남
        }
    }

    void OnCollisionEnter(Object& other) override {
        // 장애물 충돌 로직 구현
    }
};

std::vector<Obstacle> obstacles;
std::vector<Star> stars;

void InitObstacles() {
    float width100cm = 50.0f;  // 기획서의 센티미터 단위 너비
    float width300cm = 100.0f;  // 기획서의 센티미터 단위 너비

    // 화면 픽셀로 변환
    float screen_width100cm = width100cm * 10.0f;  // 예시로 1cm당 100px로 가정
    float screen_width300cm = width300cm * 50.0f;  // 예시로 1cm당 100px로 가정

    // 장애물 생성 및 초기화
    obstacles.push_back(Obstacle(1.5f, -0.5f + screen_width100cm / 2, 0.1f, screen_width100cm));
    obstacles.push_back(Obstacle(2.5f, -0.5f + screen_width300cm / 2, 0.1f, screen_width300cm));
}

void InitStars() {
    for (int i = 0; i < 5; ++i) {
        float x = (float(rand()) / RAND_MAX) * 3.0f - 1.5f;  // 초기 x 위치 랜덤
        float y = (float(rand()) / RAND_MAX) * 2.0f - 1.0f;  // 초기 y 위치 랜덤
        float size = 0.05f + (float(rand()) / RAND_MAX) * 0.1f;  // 크기 랜덤
        stars.emplace_back(x, y, size);
    }
}

void DrawObstacles() {
    for (auto& obstacle : obstacles) {
        obstacle.Draw();
    }
}

void DrawStars() {
    for (auto& star : stars) {
        star.Draw();
    }
}

void UpdateObstacles() {
    for (auto& obstacle : obstacles) {
        obstacle.Update();
    }
}

void UpdateStars() {
    for (auto& star : stars) {
        star.Update(0.00333f);  // 장애물 속도의 1/3으로 업데이트
    }
}

bool PhysicsAABB(const Object& A, const Object& B) {
    // 각 객체의 절반 폭과 절반 높이 계산
    float halfWidthA = A.width / 2;
    float halfHeightA = A.height / 2;
    float halfWidthB = B.width / 2;
    float halfHeightB = B.height / 2;

    // 각 객체의 중심 계산
    float centerX_A = A.x;
    float centerY_A = A.y;
    float centerX_B = B.x;
    float centerY_B = B.y;

    // x 및 y 축을 따라 중심 간의 거리 계산
    float distanceX = std::abs(centerX_A - centerX_B);
    float distanceY = std::abs(centerY_A - centerY_B);

    // 양 축에서 겹치는지 확인
    bool collisionX = distanceX <= halfWidthA + halfWidthB;
    bool collisionY = distanceY <= halfHeightA + halfHeightB;

    // 양 축 모두 겹칠 경우 충돌 발생
    return collisionX && collisionY;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        player.Jump();
    }
}

bool CheckCollision() {
    for (auto& obstacle : obstacles) {
        if (PhysicsAABB(player, obstacle)) {
            return true;  // 충돌 감지
        }
    }
    return false;  // 충돌 없음
}

int Physics() {
    player.ApplyGravity(gravity);

    // 장애물과 충돌 확인
    if (CheckCollision()) {
        // 충돌 감지, 게임 오버 로직 처리
        printf("Game Over!\n");
        glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);  // 창 닫기 또는 게임 오버 플래그 설정
        return -1;  // 선택적으로 게임 오버 상태를 반환할 수 있음
    }

    // 바닥(바닥)과 충돌 확인
    if (player.y - player.height / 2 <= -0.5f) {  // 땅 레벨 y = -0.5f를 기준으로 가정
        player.y = -0.5f + player.height / 2;  // 플레이어 위치를 땅 위로 조정
        player.velocityY = 0;
        player.isJumping = false;
        player.rotation = 0;
    }

    return 0;
}

int Initialize() {
    return 0;
}

int Update() {
    // 키 입력 처리 (현재는 아무 것도 하지 않음)
    return 0;
}

void DrawPlayer() {
    glPushMatrix();
    glTranslatef(player.x, player.y, 0);
    glRotatef(player.rotation, 0, 0, 1);  // 플레이어 회전 적용

    // 채워진 빨간색 사각형 그리기
    glColor3ub(255, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(-player.width / 2, -player.height / 2);
    glVertex2f(player.width / 2, -player.height / 2);
    glVertex2f(player.width / 2, player.height / 2);
    glVertex2f(-player.width / 2, player.height / 2);
    glEnd();

    // 검은색 테두리 그리기 (1px 두께)
    glColor3ub(0, 0, 0);
    glLineWidth(0.1f);  // 선의 굵기를 1px로 설정
    glBegin(GL_LINE_LOOP);
    glVertex2f(-player.width / 2, -player.height / 2);
    glVertex2f(player.width / 2, -player.height / 2);
    glVertex2f(player.width / 2, player.height / 2);
    glVertex2f(-player.width / 2, player.height / 2);
    glEnd();

    glPopMatrix();
}

void DrawFloor() {
    glColor3f(1.0f, 0.784f, 0.0588f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}

int Render() {
    glClearColor(0.0f, 0.1176f, 0.3921f, 1.0f); // RGB (0, 30, 100)를 [0.0, 1.0] 범위로 변환
    glClear(GL_COLOR_BUFFER_BIT);

    DrawStars();
    DrawObstacles();
    DrawFloor();
    DrawPlayer();

    return 0;
}

void errorCallback(int error, const char* description) {
    printf("GLFW Error: %s\n", description);
}

int main(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    Initialize();
    InitObstacles();
    InitStars();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        Physics();
        Update();
        UpdateObstacles();
        UpdateStars();
        Render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
