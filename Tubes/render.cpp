#include "game.h"

GLuint loadBMP_custom(const char *imagepath)
{
    // Membaca file gambar format BMP 24-bit untuk dijadikan tekstur background OpenGL
    FILE *file = fopen(imagepath, "rb");
    if (!file)
        return 0;
    unsigned char header[54];
    if (fread(header, 1, 54, file) != 54 || header[0] != 'B' || header[1] != 'M')
        return 0;
    unsigned int dataPos = *(int *)&(header[0x0A]);
    unsigned int imageSize = *(int *)&(header[0x22]);
    unsigned int width = *(int *)&(header[0x12]);
    unsigned int height = *(int *)&(header[0x16]);
    if (imageSize == 0)
        imageSize = width * height * 3;
    if (dataPos == 0)
        dataPos = 54;
    unsigned char *data = new unsigned char[imageSize];
    fread(data, 1, imageSize, file);
    fclose(file);
    for (unsigned int i = 0; i < imageSize; i += 3)
    {
        unsigned char tmp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = tmp;
    }
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    delete[] data;
    return textureID;
}

void drawText(float x, float y, const char *string)
{
    // Menggambar teks pada koordinat absolut statis
    glRasterPos2f(x, y);
    for (const char *c = string; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void drawTextCentered(float y, const char *string)
{
    // Menggambar teks tepat di tengah layar horizontal
    int textWidth = 0;
    for (const char *c = string; *c != '\0'; c++)
        textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, *c);
    float x = -((float)textWidth / glutGet(GLUT_WINDOW_WIDTH)) * 13.0f;
    glRasterPos2f(x, y);
    for (const char *c = string; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
}

void drawDropShadow(float x, float y, float radius)
{
    // Merender bidang gelap berbentuk lingkaran pipih di lantai Y terbawah menggunakan poligon matematis murni
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    glPushMatrix();
    glTranslatef(x, -9.5f, 0.0f);
    glScalef(1.0f, 0.01f, 0.5f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10)
    {
        float rad = i * 3.14159f / 180.0f;
        glVertex3f(cos(rad) * radius, sin(rad) * radius, 0.0f);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

void drawPlayerShip()
{
    // Menggambar pesawat pemain dengan shading material yang memantulkan cahaya
    drawDropShadow(shipX, shipY, 3.0f);

    glPushMatrix();
    glTranslatef(shipX, shipY, 0.0f);
    glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(15.0f, 0.0f, 1.0f, 0.0f);

    if (isDashing)
        glColor3f(1.0f, 1.0f, 1.0f);
    else
        glColor3f(0.0f, 0.5f, 0.8f);

    glPushMatrix();
    glScalef(2.5f, 0.6f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(0.0f, 0.8f, 1.0f);
    glPushMatrix();
    glTranslatef(1.25f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glutSolidCone(0.4f, 1.0f, 16, 16);
    glPopMatrix();

    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(-0.2f, 0.0f, 0.0f);
    glScalef(1.0f, 0.1f, 2.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(0.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.2f, 0.3f, 0.0f);
    glScalef(1.2f, 0.8f, 0.8f);
    glutSolidSphere(0.4f, 16, 16);
    glPopMatrix();

    glPopMatrix();
}

void drawEnemyShip(float ex, float ey)
{
    // Menggambar kapal musuh bergaya saucer dengan torus pengikat bercahaya
    drawDropShadow(ex, ey, 2.0f);

    glPushMatrix();
    glTranslatef(ex, ey, 0.0f);
    glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(glutGet(GLUT_ELAPSED_TIME) * 0.2f, 0.0f, 1.0f, 0.0f);

    glColor3f(0.6f, 0.6f, 0.6f);
    glPushMatrix();
    glScalef(1.8f, 0.3f, 1.8f);
    glutSolidSphere(0.5f, 20, 20);
    glPopMatrix();

    glColor3f(0.2f, 0.9f, 0.2f);
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, 0.0f);
    glScalef(1.0f, 0.8f, 1.0f);
    glutSolidSphere(0.35f, 16, 16);
    glPopMatrix();

    glColor3f(1.0f, 0.2f, 0.2f);
    glPushMatrix();
    glScalef(1.0f, 0.2f, 1.0f);
    glutSolidTorus(0.08f, 0.85f, 16, 32);
    glPopMatrix();

    glPopMatrix();
}

void drawBoss()
{
    // Menggambar geometri tiga tipe bos beserta animasi jatuh saat bos dikalahkan
    if (!currentBoss.active)
        return;
    drawDropShadow(currentBoss.x, currentBoss.y, 6.0f);

    glPushMatrix();
    glTranslatef(currentBoss.x, currentBoss.y, 0.0f);
    if (currentBoss.isDying)
        glRotatef(currentBoss.rot, 0.0f, 0.0f, 1.0f);
    else
        glRotatef(glutGet(GLUT_ELAPSED_TIME) * 0.1f, 0.0f, 1.0f, 0.0f);

    if (currentBoss.type == 1)
    {
        glColor3f(0.7f, 0.7f, 0.8f);
        glPushMatrix();
        glScalef(4.0f, 1.0f, 4.0f);
        glutSolidSphere(1.0f, 32, 32);
        glPopMatrix();

        glColor3f(0.0f, 1.0f, 1.0f);
        glutSolidTorus(0.5f, 4.0f, 16, 32);
    }
    else if (currentBoss.type == 2)
    {
        glColor3f(0.2f, 0.8f, 0.2f);
        glutSolidSphere(2.5f, 32, 32);

        glColor3f(0.8f, 0.1f, 0.1f);
        for (int i = 0; i < 360; i += 45)
        {
            glPushMatrix();
            glRotatef(i, 0.0f, 0.0f, 1.0f);
            glTranslatef(0.0f, 2.5f, 0.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            glutSolidCone(0.5f, 2.0f, 16, 16);
            glPopMatrix();
        }
    }
    else if (currentBoss.type == 3)
    {
        if (currentBoss.isInvulnerable && !currentBoss.isDying)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(1.0f, 1.0f, 0.0f, 0.4f);
            glutSolidSphere(4.5f, 32, 32);
            glDisable(GL_BLEND);
        }

        glColor3f(0.1f, 0.1f, 0.1f);
        glutSolidSphere(3.0f, 32, 32);

        glColor3f(1.0f, 0.0f, 0.0f);
        for (int i = 0; i < 360; i += 30)
        {
            for (int j = -45; j <= 45; j += 45)
            {
                glPushMatrix();
                glRotatef(i, 0.0f, 1.0f, 0.0f);
                glRotatef(j, 1.0f, 0.0f, 0.0f);
                glTranslatef(0.0f, 0.0f, 3.0f);
                glutSolidCone(0.8f, 3.5f, 8, 8);
                glPopMatrix();
            }
        }
    }
    glPopMatrix();
}

void drawMeteor(float mx, float my, float rot)
{
    // Menggambar bongkahan batu meteor dengan shading warna cokelat menggunakan dodecahedron primitif
    drawDropShadow(mx, my, 2.5f);
    glPushMatrix();
    glTranslatef(mx, my, 0.0f);
    glRotatef(rot, 1.0f, 1.0f, 1.0f);
    glScalef(1.5f, 1.5f, 1.5f);
    glColor3f(0.5f, 0.3f, 0.1f);
    glutSolidDodecahedron();
    glPopMatrix();
}

void drawBullets()
{
    // Menggambar proyektil kuning bercahaya untuk pemain
    glColor3f(1.0f, 1.0f, 0.0f);
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            glPushMatrix();
            glTranslatef(bullets[i].x, bullets[i].y, 0.0f);
            glutSolidSphere(0.15f, 10, 10);
            glPopMatrix();
        }
    }
}

void drawEnemyBullets()
{
    // Menggambar proyektil merah mematikan yang ditembakkan oleh musuh
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (enemyBullets[i].active)
        {
            glPushMatrix();
            glTranslatef(enemyBullets[i].x, enemyBullets[i].y, 0.0f);
            glutSolidSphere(0.15f, 10, 10);
            glPopMatrix();
        }
    }
}

void drawExplosions()
{
    // Merender serpihan partikel ledakan yang mengecil perlahan
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    for (int i = 0; i < MAX_EXPLOSIONS; i++)
    {
        if (explosions[i].active)
        {
            glColor4f(1.0f, 0.5f, 0.0f, explosions[i].life);
            glPushMatrix();
            glTranslatef(explosions[i].x, explosions[i].y, 0.0f);
            glutSolidCube(0.4f * explosions[i].life);
            glPopMatrix();
        }
    }

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

void drawPowerUps()
{
    // Menggambar kotak power-up berputar dengan warna solid
    for (int i = 0; i < MAX_POWERUPS; i++)
    {
        if (powerups[i].active)
        {
            glPushMatrix();
            glTranslatef(powerups[i].x, powerups[i].y, 0.0f);
            glRotatef(glutGet(GLUT_ELAPSED_TIME) * 0.1f, 1, 1, 0);

            if (powerups[i].type == 0)
                glColor3f(0.0f, 1.0f, 0.0f);
            else if (powerups[i].type == 1)
                glColor3f(1.0f, 0.0f, 1.0f);
            else if (powerups[i].type == 2)
                glColor3f(1.0f, 0.0f, 0.0f);

            glutSolidCube(0.7f);
            glPopMatrix();
        }
    }
}

void drawParallaxBackground3D()
{
    // Merender gambar background Mars di Orthogonal 2D dilanjut dengan hujan badai pasir merah 3D
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (bgTexture)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, bgTexture);
        glColor3f(1.0f, 1.0f, 1.0f);

        float offsetU = camX * 0.003f;
        float offsetV = camY * 0.003f;

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f + offsetU, 0.0f + offsetV);
        glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f + offsetU, 0.0f + offsetV);
        glVertex2f(1.0f, 0.0f);
        glTexCoord2f(1.0f + offsetU, 1.0f + offsetV);
        glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0f + offsetU, 1.0f + offsetV);
        glVertex2f(0.0f, 1.0f);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glLineWidth(2.0f);
    glBegin(GL_LINES);
    // for (int i = 0; i < MAX_SAND; i++)
    // {
    //     glColor4f(0.9f, 0.4f, 0.1f, 0.6f);
    //     glVertex3f(sand[i].x, sand[i].y, -5.0f);
    //     glColor4f(0.9f, 0.2f, 0.0f, 0.0f);
    //     glVertex3f(sand[i].x + (sand[i].speedX * 0.1f), sand[i].y + (sand[i].speedY * 0.1f), -5.0f);
    // }
    glEnd();
    glLineWidth(1.0f);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void drawMenuBorder()
{
    // Membuat garis batas estetis di sudut layar untuk menu utama
    glColor3f(0.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-12.0f, 9.0f);
    glVertex2f(-12.0f, 7.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(-12.0f, 9.0f);
    glVertex2f(-10.0f, 9.0f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(12.0f, 9.0f);
    glVertex2f(12.0f, 7.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(12.0f, 9.0f);
    glVertex2f(10.0f, 9.0f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(-12.0f, -9.0f);
    glVertex2f(-12.0f, -7.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(-12.0f, -9.0f);
    glVertex2f(-10.0f, -9.0f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(12.0f, -9.0f);
    glVertex2f(12.0f, -7.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(12.0f, -9.0f);
    glVertex2f(10.0f, -9.0f);
    glEnd();
    glLineWidth(1.0f);
}

void drawMenuScreen()
{
    // Render teks dan batas untuk Menu Utama
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-13.0, 13.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    drawMenuBorder();
    glColor3f(0.0f, 1.0f, 1.0f);
    drawTextCentered(2.0f, "PLATYPUS");
    glColor3f(1.0f, 1.0f, 1.0f);
    drawTextCentered(0.0f, "Tekan [ENTER] untuk Mulai");
    glColor3f(0.5f, 0.5f, 0.5f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void drawGameOverScreen()
{
    // Render layar Game Over
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-13.0, 13.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glColor3f(1.0f, 0.0f, 0.0f);
    drawTextCentered(2.0f, "GAME OVER");
    char scoreStr[64];
    sprintf(scoreStr, "Final Score: %d", score);
    glColor3f(1.0f, 1.0f, 0.0f);
    drawTextCentered(0.0f, scoreStr);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawTextCentered(-2.0f, "Press [R] to Play Again");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void drawVictoryScreen()
{
    // Render layar kemenangan setelah melewati 15 wave
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-13.0, 13.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    drawMenuBorder();
    glColor3f(0.0f, 1.0f, 0.0f);
    drawTextCentered(2.0f, "VICTORY! MARS SECURED!");
    char scoreStr[64];
    sprintf(scoreStr, "Final Score: %d", score);
    glColor3f(1.0f, 1.0f, 0.0f);
    drawTextCentered(0.0f, scoreStr);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawTextCentered(-2.0f, "Press [R] to Return to Base");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void drawUI()
{
    // Render HUD, peringatan wave, dan bar nyawa bos
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-13.0, 13.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    char scoreStr[64];
    sprintf(scoreStr, "SCORE: %d   WAVE: %d", score, currentWave);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(6.0f, 9.0f, scoreStr);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-12.5f, 9.1f, "LIVES: ");
    for (int i = 0; i < playerHP; i++)
    {
        glPushMatrix();
        glTranslatef(-10.0f + (i * 0.8f), 9.3f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.1f, 0.2f);
        glVertex2f(-0.1f, 0.2f);
        glVertex2f(-0.2f, 0.0f);
        glEnd();
        glPopMatrix();
    }

    if (dashCooldown == 0)
    {
        glColor3f(0.0f, 1.0f, 1.0f);
        drawText(-12.5f, 8.3f, "DASH: READY (SPACE)");
    }
    else
    {
        glColor3f(0.5f, 0.5f, 0.5f);
        drawText(-12.5f, 8.3f, "DASH: COOLDOWN");
    }

    if (waveMessageTimer > 0 && !currentBoss.isDying)
    {
        char waveMsg[64];
        if (currentWave % 5 == 0 && currentWave <= 15)
            sprintf(waveMsg, "WARNING: BOSS APPROACHING!");
        else
            sprintf(waveMsg, "WAVE %d", currentWave);
        glColor3f(1.0f, 0.0f, 0.0f);
        drawTextCentered(0.0f, waveMsg);
    }

    if (currentBoss.active && !currentBoss.isDying)
    {
        if (currentBoss.isInvulnerable)
            glColor3f(1.0f, 1.0f, 0.0f);
        else
            glColor3f(1.0f, 0.0f, 0.0f);

        glBegin(GL_QUADS);
        glVertex2f(-5.0f, 8.5f);
        glVertex2f(-5.0f + (10.0f * (currentBoss.hp / currentBoss.maxHp)), 8.5f);
        glVertex2f(-5.0f + (10.0f * (currentBoss.hp / currentBoss.maxHp)), 8.8f);
        glVertex2f(-5.0f, 8.8f);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(-5.0f, 8.5f);
        glVertex2f(5.0f, 8.5f);
        glVertex2f(5.0f, 8.8f);
        glVertex2f(-5.0f, 8.8f);
        glEnd();
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void display()
{
    // Mengumpulkan dan mengeksekusi semua panggilan gambar berdasarkan urutan lapisan yang benar dengan efek goyangan kamera besar
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float finalCamX = camX;
    float finalCamY = camY;
    if (shakeTimer > 0 && currentState == PLAYING)
    {
        finalCamX += ((rand() % 100) / 100.0f - 0.5f) * 1.5f;
        finalCamY += ((rand() % 100) / 100.0f - 0.5f) * 1.5f;
    }

    gluLookAt(finalCamX, finalCamY, camZ, targetX, targetY, targetZ, 0.0f, 1.0f, 0.0f);
    drawParallaxBackground3D();

    if (currentState == MENU)
        drawMenuScreen();
    else if (currentState == GAME_OVER)
        drawGameOverScreen();
    else if (currentState == VICTORY)
        drawVictoryScreen();
    else if (currentState == PLAYING)
    {
        drawExplosions();
        drawPlayerShip();
        drawBoss();
        for (int i = 0; i < MAX_METEORS; i++)
            if (meteors[i].active)
                drawMeteor(meteors[i].x, meteors[i].y, meteors[i].rot);
        for (int i = 0; i < MAX_ENEMIES; i++)
            if (enemies[i].active)
                drawEnemyShip(enemies[i].x, enemies[i].y);
        drawPowerUps();
        drawBullets();
        drawEnemyBullets();
        drawUI();
    }

    glutSwapBuffers();
}