FROM alpine:latest
RUN apk --no-cache add cmake clang clang-dev make gcc g++ libc-dev linux-headers
ADD ./app /app/app
ADD ./CMakeLists.txt /app
WORKDIR /app
RUN mkdir build
WORKDIR /app/build
RUN cmake ..
RUN make
CMD ./server
