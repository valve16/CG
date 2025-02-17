const canvas = document.getElementById('truckCanvas');
const ctx = canvas.getContext('2d');

class Truck {
    constructor() {
        this.x = 0; // Начальная позиция грузовика по X
        this.y = 0; // Начальная позиция грузовика по Y
        this.isDragging = false; // Флаг для отслеживания перетаскивания
        this.offsetX = 0; // Смещение по X относительно начальной точки
        this.offsetY = 0; // Смещение по Y относительно начальной точки
    }

    // Метод для отрисовки круга (колесо)
    drawCircle(x, y, radius, color) {
        ctx.beginPath();
        ctx.arc(x, y, radius, 0, Math.PI * 2);
        ctx.fillStyle = color;
        ctx.fill();
        ctx.closePath();
    }

    // Метод для отрисовки дороги
    drawRoad() {
        ctx.fillStyle = 'green';
        ctx.fillRect(0, 650, 900, 50);
        ctx.fillStyle = 'black';
        ctx.fillRect(0, 650, 900, 10);
    }

    // Метод для отрисовки рамы грузовика
    drawFrame() {
        ctx.beginPath();
        ctx.lineTo(this.x + 100, this.y + 580);
        ctx.lineTo(this.x + 820, this.y + 580);
        ctx.lineTo(this.x + 840, this.y + 500);
        ctx.lineTo(this.x + 90, this.y + 500);
        ctx.fillStyle = '#2b2a2a';
        ctx.fill();
        ctx.stroke();
    }

    // Метод для отрисовки окна
    drawWindow() {
        ctx.beginPath();
        ctx.moveTo(this.x + 700, this.y + 350);
        ctx.lineTo(this.x + 785, this.y + 350);
        ctx.lineTo(this.x + 810, this.y + 410);
        ctx.lineTo(this.x + 700, this.y + 410);
        ctx.lineTo(this.x + 700, this.y + 350);
        ctx.fillStyle = '#1f80b8';
        ctx.fill();
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(this.x + 803, this.y + 340);
        ctx.lineTo(this.x + 813, this.y + 340);
        ctx.lineTo(this.x + 843, this.y + 415);
        ctx.lineTo(this.x + 833, this.y + 415);
        ctx.lineTo(this.x + 803, this.y + 340);
        ctx.fillStyle = '#1f80b8';
        ctx.fill();
        ctx.stroke();
    }

    // Метод для отрисовки кабины
    drawCab() {
        ctx.beginPath();
        ctx.moveTo(this.x + 650, this.y + 310);
        ctx.lineTo(this.x + 800, this.y + 310);
        ctx.lineTo(this.x + 850, this.y + 430);
        ctx.lineTo(this.x + 855, this.y + 490);
        ctx.lineTo(this.x + 850, this.y + 530);
        ctx.lineTo(this.x + 750, this.y + 530);
        ctx.lineTo(this.x + 690, this.y + 490);
        ctx.lineTo(this.x + 650, this.y + 490);
        ctx.lineTo(this.x + 650, this.y + 310);
        ctx.fillStyle = '#ff9633';
        ctx.fill();
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(this.x + 690, this.y + 340);
        ctx.lineTo(this.x + 790, this.y + 340);
        ctx.lineTo(this.x + 820, this.y + 410);
        ctx.lineTo(this.x + 820, this.y + 515);
        ctx.lineTo(this.x + 760, this.y + 515);
        ctx.lineTo(this.x + 690, this.y + 470);
        ctx.lineTo(this.x + 690, this.y + 340);
        ctx.fillStyle = '#c2752d';
        ctx.fill();
        ctx.stroke();

        this.drawWindow();
    }

    // Метод для отрисовки кузова
    drawBodywork() {
        ctx.beginPath();
        ctx.moveTo(this.x + 90, this.y + 330);
        ctx.lineTo(this.x + 530, this.y + 330);
        ctx.lineTo(this.x + 455, this.y + 500);
        ctx.lineTo(this.x + 90, this.y + 500);
        ctx.lineTo(this.x + 20, this.y + 470);
        ctx.lineTo(this.x + 90, this.y + 330);
        ctx.fillStyle = '#ff9633';
        ctx.fill();
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(this.x + 530, this.y + 330);
        ctx.lineTo(this.x + 555, this.y + 280);
        ctx.lineTo(this.x + 690, this.y + 280);
        ctx.lineTo(this.x + 670, this.y + 295);
        ctx.lineTo(this.x + 630, this.y + 295);
        ctx.lineTo(this.x + 610, this.y + 340);
        ctx.lineTo(this.x + 575, this.y + 340);
        ctx.lineTo(this.x + 510, this.y + 500);
        ctx.lineTo(this.x + 455, this.y + 500);
        ctx.fillStyle = '#ff9633';
        ctx.fill();
        ctx.stroke();
    }

    // Метод для отрисовки грузовика
    draw() {
        ctx.clearRect(0, 0, canvas.width, canvas.height); // Очистка холста
        this.drawRoad();
        this.drawFrame();
        this.drawCircle(this.x + 180, this.y + 585, 65, '#000'); // Колеса
        this.drawCircle(this.x + 700, this.y + 585, 65, '#000');
        this.drawCircle(this.x + 350, this.y + 585, 65, '#000');
        this.drawCircle(this.x + 180, this.y + 585, 25, '#787474'); // Колеса
        this.drawCircle(this.x + 700, this.y + 585, 25, '#787474');
        this.drawCircle(this.x + 350, this.y + 585, 25, '#787474');
        this.drawCab();
        this.drawBodywork();

        ctx.beginPath();
        ctx.strokeStyle = '#000';
        ctx.lineWidth = 2;
        ctx.stroke();
        ctx.closePath();

        ctx.fillStyle = '#fff';
        ctx.font = '16px Arial';
        ctx.fillText('Truck', this.x + 90, this.y + 260);
    }

    // Метод для обработки начала перетаскивания
    startDrag(mouseX, mouseY) {
        if (
            mouseX >= this.x && mouseX <= this.x + 840 &&
            mouseY >= this.y && mouseY <= this.y + 580
        ) {
            this.isDragging = true;
            this.offsetX = mouseX - this.x;
            this.offsetY = mouseY - this.y;
        }
    }

    // Метод для обработки перемещения мыши
    drag(mouseX, mouseY) {
        if (this.isDragging) {
            this.x = mouseX - this.offsetX;
            this.y = mouseY - this.offsetY;
            this.draw();
        }
    }

    // Метод для завершения перетаскивания
    stopDrag() {
        this.isDragging = false;
    }
}

// Создаем экземпляр грузовика
const truck = new Truck();

// Обработчики событий мыши
canvas.addEventListener('mousedown', (e) => {
    const rect = canvas.getBoundingClientRect();
    const mouseX = e.clientX - rect.left;
    const mouseY = e.clientY - rect.top;
    truck.startDrag(mouseX, mouseY);
});

canvas.addEventListener('mousemove', (e) => {
    const rect = canvas.getBoundingClientRect();
    const mouseX = e.clientX - rect.left;
    const mouseY = e.clientY - rect.top;
    truck.drag(mouseX, mouseY);
});

canvas.addEventListener('mouseup', () => {
    truck.stopDrag();
});

canvas.addEventListener('mouseleave', () => {
    truck.stopDrag();
});

// Начальная отрисовка грузовика
truck.draw();