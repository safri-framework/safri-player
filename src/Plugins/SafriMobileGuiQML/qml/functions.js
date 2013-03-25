function myRGBA(r, g, b , a)

{
    r = (1 / 255) * r;
    g = (1 / 255) * g;
    b = (1 / 255) * b;
    a = a / 100;

    return Qt.rgba(r, g, b,a)
}

function scale(x)
{
    return Math.round(x * 1.6)
}
