
void execute() {
    static uint32_t tm = 0;


    tm = tm + 1;
    if (ctx->finished) return;
    switch (ctx->ip) {
        case 0:;
            ctx->ip = 0;
            break;
        case 5:
            if (!(needUpdate)) goto lbl__false_168;;
            ctx->ip = 5;
            break;
        case 10:
            needUpdate = false;
            row = 0;
            ctx->ip = 10;
            break;
        case 15:
            updateText();
            ctx->ip = 15;
            break;
        case 20:
        lbl__while_174:
            col = 0;
            ctx->ip = 20;
            break;
        case 25:
            Lcd7567.renderPartial(row, 0);
            col += 1;
            ctx->ip = 25;
            break;
        case 30:
            row += 1;
            ctx->ip = 30;
            break;
        case 35:
            if (row < 64 / 8) goto lbl__while_174;
            ctx->ip = 35;
            break;
        case 40:
            goto lbl__end_168;
            ctx->ip = 40;
            break;
        case 45:
        lbl__false_168:;
            ctx->ip = 45;
            break;
        case 50:
        lbl__end_168:;
            ctx->ip = 50;
            break;
        case 55:
            if (!(tm > 5000)) goto lbl__false_189;;
            ctx->ip = 55;
            break;
        case 60:
            static ThreadFunc *refreshCTX =

                    __null;
            ctx->ip = 60;
            break;
        case 65:
            if (refreshCTX ==

                __null

                    )
                refreshCTX = new ThreadFunc();;
            ctx->ip = 65;
            break;
        case 70:
        lbl__while_190:
            Lcd7567.refresh(refreshCTX);
            ctx->ip = 70;
            break;
        case 75:
            if (!refreshCTX->ctx->done) goto lbl__while_190;
            ctx->ip = 75;
            break;
        case 80:;
            ctx->ip = 80;
            break;
        case 85:
            delete refreshCTX;
            refreshCTX =

                    __null;;
            ctx->ip = 85;
            break;
        case 90:
            tm %= 5000;
            ctx->ip = 90;
            break;
        case 95:;
            ctx->ip = 95;
            break;
        case 100:
            goto lbl__end_189;
            ctx->ip = 100;
            break;
        case 105:
        lbl__false_189:;
            ctx->ip = 105;
            break;
        case 110:
        lbl__end_189:;
            ctx->ip = 110;
            break;
        case 115:;
            ctx->ip = 115;
            break;
        case 120:;
            ctx->ip = 120;
            break;
        default:
            ctx->done = ctx->ip > 120;
            if (ctx->done) { if (ctx->type == THREAD_EXECUTION::FOREVER) ctx->ip = -1; else ctx->finished = 1; }
            break;
    }
    ctx->ip += 1;

    ;

};
