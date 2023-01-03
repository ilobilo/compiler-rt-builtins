#ifndef ASSERT__H
#define ASSERT__H

#define assert(exp) do { if (!(exp)) for (;;) { } } while (0)

#endif // ASSERT__H