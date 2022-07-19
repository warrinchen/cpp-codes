int dist = 0;
void say(int d) {
    char str[20];
    sprintf(str, "前方有障碍, 距离小车车%d厘米", d);
    gpp_say(1, str);
}
for (;;) {
    forward(1, 10);
    dist = distsensor();
    if (dist < 20) {
        say(dist);
        cexit();
    }
}

void main() {}