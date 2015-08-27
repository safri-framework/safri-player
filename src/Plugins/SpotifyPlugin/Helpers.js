.pragma library

function transparentColor(color, opacity)
{
    var number = Math.round((opacity/100) * 255);
    number = number.toString(16);
    var result = "#"+number+color;
    return result
}
