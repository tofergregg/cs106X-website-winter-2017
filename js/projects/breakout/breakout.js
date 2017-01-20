var STAGE_WIDTH = 420;
var STAGE_HEIGHT = 600;

/* local game state */
var TOP_GAP = 70; //Gap from top wall to firs brick
var BRICK_GAP = 4; // Gap between bricks
var BRICKS_ROW = 10; // Number of bricks in a row
var NUM_ROWS = 10; // Number of rows of bricks

var BRICK_WIDTH = Math.floor((STAGE_WIDTH - (BRICKS_ROW + 1.0)*BRICK_GAP)/BRICKS_ROW);
var BRICK_HEIGHT = 8;

var BALL_RADIUS = 10;

var PADDLE_WIDTH = 60;
var PADDLE_HEIGHT = 10;

var bricksLeft = 100; // number of bricks left on the screen. if 0, player wins

var colors = [Color.red, Color.orange, Color.yellow, Color.green, Color.cyan];

var ball;
var paddle;

var numlives = 3;

var clickToStartLabel;

/**
 * We create all the gameplay elements here: ball, paddle, and bricks!
 */
function run() {
    setBackground(STAGE_WIDTH, STAGE_HEIGHT, Color.white, 'breakoutDemo');
    for (var i=0; i < NUM_ROWS; ++i) {
        for (var j=0; j < BRICKS_ROW; ++j) {
            var rect = new GRect(2+BRICK_GAP + (i*(BRICK_WIDTH+BRICK_GAP)), 
                                 TOP_GAP + BRICK_GAP + (j*(BRICK_HEIGHT+BRICK_GAP)), 
                                 BRICK_WIDTH, BRICK_HEIGHT);
            rect.setColor(colors[Math.floor(j/2)]);
            add(rect);
        }
    }
    
    ball = new GCircle(200,400,BALL_RADIUS * 2);
    ball.vx = Math.random()*4 + 1;
    ball.vy = Math.abs(Math.random())*2 + 5;
    if (Math.random() > .5)
       ball.vx = -ball.vx;
    add(ball);
    
    paddle = new GRect(180,570,PADDLE_WIDTH,PADDLE_HEIGHT);
    add(paddle);

    clickToStartLabel = new GLabel("Click To Start");
    clickToStartLabel.position.x = STAGE_WIDTH/2 - clickToStartLabel._width/2;
    clickToStartLabel.position.y = STAGE_HEIGHT/2;
    add(clickToStartLabel);
    renderer.render(stage);
}

/**
 * Detect when the ball has hit any of the walls. The ball
 * bounces off the north, east, and west walls, and indicates
 * failure if the ball goes off the bottom of the screen
 */
function detectWalls() {
    if (ball.position.y > STAGE_HEIGHT) {
        if (--numlives <= 0) {
            var text = new PIXI.Text("YOU LOSE", {font:"50px Arial", fill:"red"});
            text.position.x = STAGE_WIDTH/2 - text._width/2;
            text.position.y = STAGE_HEIGHT/2;
            stage.addChild(text);
            ball.vx = 0;
            ball.vy = 0;
            return;
        } else {

                ball.position.x = 200;
                ball.position.y = 400;
                ball.vx = ball.vy = 0;

                //requestAnimFrame(function() {});
                //setTimeout(function(){
                //      ball.vx = Math.random()*4 + 1;
                //     ball.vy = Math.random()*2 + 3;
                //    if (Math.random() > .5)
                 //       ball.vx = -ball.vx;
                //}, 1000);
        }
    } else if (ball.position.x < 0 || ball.position.x > STAGE_WIDTH) {
        ball.vx = -ball.vx;
    } else if (ball.position.y <= 0) {
        ball.vy = -Math.abs(ball.vy);   
    }
}

function pauseFunc() {
	ball.vx = Math.random()*2+1;
	ball.vy = Math.random()*3 + 2;
	if (Math.random() > .5)
		ball.vx = -ball.vx;
}
/**
 * Detect a collision between the ball and another object!
 * If it collides with any element (brick or paddle), we
 * reverse its y direction. In addition, if the collider
 * is a brick, we remove the brick
 */
function detectCollision() {
    
    detectWalls();
    for (var i=0; i<=BALL_RADIUS; i+=BALL_RADIUS) {
        for (var j=0; j<BALL_RADIUS; j+=BALL_RADIUS) {
            var collider = stage.getElementAt(ball.position.x+i, ball.position.y+j);
            if (collider !== null) {
                if (collider !== paddle) {
                    stage.remove(collider);
                    bricksLeft -= 1;
		    ball.vy = -ball.vy;
                } else {
		    ball.vy = -Math.abs(ball.vy);
		}
                return;
            }
        }
    }
}

var pause = false;
/**
 * This function is called inside a loop to animate the
 * game. Here is where we update the positions of all the
 * elements in the game and remove / add elements
 * with response to gameplay events (collisions, win/loss, etc)
 */
function drawFrame() {
    if (pause === "undefined" || pause === false) {
        ball.position.x += ball.vx;
        ball.position.y += ball.vy;
    }
    
    detectCollision();
    
    var mousex = stage.getMousePosition().x;
    if (mousex > 0 && mousex < STAGE_WIDTH-PADDLE_WIDTH) {
        paddle.position.x = mousex;
    }
    if (bricksLeft === 0) {
        var text = new PIXI.Text("YOU WIN", {font:"50px Arial", fill:"red"});
        text.position.x = STAGE_WIDTH/2 - text._width/2;
        text.position.y = STAGE_HEIGHT/2;
        stage.addChild(text);
        ball.vx = 0;
        ball.vy = 0;
    }
}
