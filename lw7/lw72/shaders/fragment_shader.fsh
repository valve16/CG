varying vec2 v_uv;

#define GOLD vec4(1.0, 0.85, 0.1, 1.0)
#define RED vec4(0.75, 0.1, 0.1, 1.0)

// Прямоугольник
float box(vec2 p, vec2 center, vec2 radius) {
    vec2 d = abs(p - center) - radius * 0.5;
    return step(max(d.x, d.y), 0.0);
}

vec2 rotate(vec2 point, vec2 center, float angle) {
    float s = sin(angle);
    float c = cos(angle);
    point -= center;
    vec2 rotated = vec2(
        point.x * c - point.y * s,
        point.x * s + point.y * c
    );
    return rotated + center;
}

float leftTrapezoid(vec2 p, vec2 center, float height, float leftWidth, float rightWidth) {
    vec2 local = p - center;

    // Проверка по вертикали
    if (abs(local.y) > height * 0.5) return 0.0;

    // Нормализованная вертикальная координата: 0 (низ) → 1 (верх)
    float t = (local.y + height * 0.5) / height;

    // Левая граница фиксирована
    float left = -leftWidth * 0.5;

    // Правая граница интерполируется
    float right = mix(leftWidth, rightWidth, t) * 0.5;

    return step(left, local.x) * step(local.x, right);
}

float drawHammer(vec2 uv, vec2 center, float size, float angle) {
    float hammer = 0.0;
    
    // Размеры компонентов молота
    vec2 handleSize = vec2(0.06 * size, 0.4 * size); // Ручка
    //vec2 headSize = vec2(0.2 * size, 0.09 * size);   // Головка
    
    // Вращаем координаты относительно центра
    vec2 rotatedUV = rotate(uv, center, angle);
    
    // Позиции компонентов относительно центра (уже повёрнутые)
    vec2 handlePos = center + vec2(-0.15 * size, 0.0 * size);
    vec2 headPos = center + vec2(-0.13 * size, 0.16 * size);
    
    // Рисуем компоненты
    hammer += box(rotatedUV, handlePos, handleSize); // Ручка
    hammer += leftTrapezoid(rotatedUV, headPos, 0.09 * size, 0.25 * size, 0.05 * size);     // Головка
    
    return step(0.5, hammer);
}

//серп
float crescent(vec2 p, vec2 center, float outerRadius, float innerRadius, float offset, float angle) { 
    p = rotate(p, center, angle);
    float distOuter = length(p - center);
    float distInner = length(p - (center - vec2(offset, 0.0)));
    return step(distOuter, outerRadius) * (1.0 - step(distInner, innerRadius));
}


float distanceToLine(vec2 p, vec2 a, vec2 b) {
    vec2 pa = p - a;
    vec2 ba = b - a;
    float h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
    return length(pa - ba * h);
}

// звезда
float starOutline(vec2 p, vec2 center, float radius, float thickness) {
    const float PI = 3.14159265359;
    float angleOffset = PI / 2.0;
    float innerScale = 0.5; // Соотношение внутреннего радиуса к внешнему

    // Создаем 10 точек
    vec2 points[10];
    for (int i = 0; i < 10; i++) {
        float angle = angleOffset + float(i) * PI / 5.0;
        float r = (i % 2 == 0) ? radius : radius * innerScale;
        points[i] = center + r * vec2(cos(angle), sin(angle));
    }

    // Минимальное расстояние до отрезков
    float d = 1.0;
    for (int i = 0; i < 10; i++) {
        int next = (i + 1) % 10;
        d = min(d, distanceToLine(p, points[i], points[next]));
    }

    return step(d, thickness);
}

float drawHandle(vec2 p, vec2 pos, float width, float height, float angle) {
    // Рисуем прямоугольник как рукоятку серпа слева
    p = rotate(p, pos, angle);
    vec2 handlePos = pos; // Сдвигаем влево от центра серпа
    return box(p, handlePos, vec2(width, height)); // Рисуем прямоугольник рукоятки
}

void main() {
    float flagWidth = 2.0;
    float flagHeight = 1.0;

    vec4 color = RED; // Красный фон

    vec2 hammerCenter = vec2(flagHeight / 2.5, flagHeight - flagHeight / 3.8);
    float hammerSize = 0.5; // Общий масштаб молота
    float rotationAngle = radians(-45.0); 
    // молот
    if(drawHammer(v_uv, hammerCenter, hammerSize, rotationAngle) > 0.5) {
        color = GOLD;
    }

    // серп 
    vec2 crescentCenter = vec2(flagHeight / 3, flagHeight - flagHeight / 3.4);
    float crescentOuter = flagHeight / 10.0;
    float crescentInner = crescentOuter * 1.1;
    float crescentOffset = crescentOuter * 0.4;
    float crescentAngle = radians(15.0);
    if(crescent(v_uv, crescentCenter, crescentOuter, crescentInner, crescentOffset, crescentAngle) > 0.5) {
        color = GOLD;
    }

    float handleWidth = 0.08;  
    float handleHeight = 0.035;  
    float handleAngle = radians(-45.0);
    vec2 handlePos = vec2(crescentCenter.x - 0.04, crescentCenter.y - 0.115);
    if(drawHandle(v_uv, handlePos, handleWidth, handleHeight, handleAngle) > 0.5) {
        color = GOLD;
    }

    vec2 starCenter = vec2(flagHeight / 3.0, flagHeight - flagHeight/8.0);
    float starRadius = flagHeight / 16.0;
    float lineWidth = 0.005;
    
    // звезда
    if(starOutline(v_uv, starCenter, starRadius, lineWidth) > 0.5) {
        color = GOLD;
    }

    gl_FragColor = color;
}