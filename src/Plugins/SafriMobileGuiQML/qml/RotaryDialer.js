// start angle of a dialer rotation
var startAngle = null;

// dialer center X
var centerX = null;
// dialer center Y
var centerY = null;
 var position = 0;
// the dialer stop angle
//var dialerStopAngle = Math.PI / 4;
// angle between numbers//rvar digitAngle = (3 * Math.PI / 2) / 9;

// maximum angle before the finger reaches the dialer stop
var maxAngle;
var currentAngle = 0
var lastAngle;
var flag;
var lastDiff
var pressAngle
var correctPressPoint = false;

function initialize()
{
    centerX = dialer.x + dialer.width / 2;
    centerY = dialer.y + dialer.height / 2;
}


function getEventAngle(event)
{
    var angle = Math.atan2(event.y - centerY, event.x - centerX);
    var deg = (angle/Math.PI*180) + (angle > 0 ? 0 : 360);
    return deg;
}


function getEventDist(event)
{

    var y = Math.abs(event.y - centerY);
    var x = Math.abs(event.x - centerX);
    return  Math.sqrt(x*x + y*y);
}

function getAngleDiff(angle)
{
    var diff = (angle - startAngle ) % 360;
    startAngle = (startAngle + diff + 360) % 360 ;
    return diff;
}

function dialerPressed(event)
{
    startAngle = getEventAngle(event);
    pressAngle = startAngle;
    var dist = getEventDist(event)
    if( dist > 100*scaleFactor && dist < 193*scaleFactor)
    {

        correctPressPoint = true;
        view.interactive = false;
    }
    else
        correctPressPoint = false;

}

function dialerReleased(event)
{


    view.interactive = true;
}


function dialerMoved(event)
{
    var dist = getEventDist(event)
    console.log(dist)

    if(correctPressPoint && dist > 100*scaleFactor && dist < 193*scaleFactor)
    {
        var pos = getEventAngle(event);
       // position = (currentAngle + getAngleDiff(pos) +360)%360 ;

        var diff = getAngleDiff(pos);
        var nextPos = (dialer.rotation + diff + 360 ) % 360;
        if(Math.abs(dialer.rotation - nextPos) > 50)
            diff = 0;
        if (nextPos > 242)
                diff = 0

        dialer.rotation  = (dialer.rotation + diff + 360 ) % 360;
        volumeChanged(100 / 242 * dialer.rotation);
     }

}

