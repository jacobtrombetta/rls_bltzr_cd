/** nvcc compilation aborted error
 *
 * The following coroutine code will cause the nvcc
 * complier to issue a "Compilation aborted" error.
 *
 * See will_make_compiler_fail function for code that
 * causes the compliation aborted error.
 */
#include <coroutine>
#include <cuda_runtime.h>
#include <memory>
#include <memory_resource>
#include <string>

//--------------------------------------------------------------------------------------------------
// stream_handle
//--------------------------------------------------------------------------------------------------
struct stream_handle {
  int device = 0;
  cudaStream_t stream = nullptr;
  stream_handle* next = nullptr;
};

//--------------------------------------------------------------------------------------------------
// make_stream_handle
//--------------------------------------------------------------------------------------------------
static stream_handle* make_stream_handle(int device) noexcept {
  auto res = new stream_handle{};
  cudaStreamCreate(&res->stream);
  res->device = device;
  res->next = nullptr;
  return res;
};

//--------------------------------------------------------------------------------------------------
// stream_wrapper
//--------------------------------------------------------------------------------------------------
/**
 * Simplified wrapper around a pooled CUDA stream.
 */
class stream_wrapper {
public:
  explicit stream_wrapper(int device = 0) noexcept {
    handle_ = make_stream_handle(0);
  }

  /////////////////////////////////////////////////////
  // Comment out the destructor to get the ////////////
  // will_make_compiler_fail function to to compile. //
  /////////////////////////////////////////////////////
  ~stream_wrapper() noexcept {
  }
  /////////////////////////////////////////////////////
  /////////////////////////////////////////////////////
  /////////////////////////////////////////////////////

  cudaStream_t get_stream() { return handle_->stream; }

private:
  stream_handle* handle_;
};

//--------------------------------------------------------------------------------------------------
// async_device_resource
//--------------------------------------------------------------------------------------------------
class async_device_resource final : public std::pmr::memory_resource {
public:
  explicit async_device_resource(cudaStream_t stream) noexcept
    : stream_{stream} {}

private:
  cudaStream_t stream_;

  void* do_allocate(size_t bytes, size_t alignment) noexcept override {
        void* res;
        cudaMallocAsync(&res, bytes, stream_);
        return res;
    }

  void do_deallocate(void* ptr, size_t bytes, size_t alignment) noexcept override {
    cudaFreeAsync(ptr, stream_);
  }

  bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
    return this == &other;
  }
};

//--------------------------------------------------------------------------------------------------
// future, promise_type
//--------------------------------------------------------------------------------------------------
template<typename T>
  struct future {
      std::shared_ptr<T> value;
      future(std::shared_ptr<T> p): value(p) {}
      ~future() {}
      T get() {return *value;}

  struct promise_type {
      std::shared_ptr<T> ptr = std::make_shared<T>();
      ~promise_type() {}
      future<T> get_return_object() {return ptr;}
      void return_value(T v) {*ptr = v;}
      std::suspend_never initial_suspend() {return {};}
      std::suspend_never final_suspend() noexcept {return {};}
      void unhandled_exception() {std::exit(1);}
  };
};

//--------------------------------------------------------------------------------------------------
// will_not_make_compiler_fail_1
//--------------------------------------------------------------------------------------------------
static future<int> will_not_make_compiler_fail_1() noexcept {
    stream_wrapper stream;
    co_return int{};
}

//--------------------------------------------------------------------------------------------------
// will_not_make_compiler_fail_2
//--------------------------------------------------------------------------------------------------
static future<int> will_not_make_compiler_fail_2() noexcept {
    async_device_resource resource{cudaStream_t{}};
    co_return int{};
}

//--------------------------------------------------------------------------------------------------
// will_not_make_compiler_fail_3
//--------------------------------------------------------------------------------------------------
static future<int> will_not_make_compiler_fail_3() noexcept {
    co_return int{};
}

//--------------------------------------------------------------------------------------------------
// will_make_compiler_fail
//--------------------------------------------------------------------------------------------------
/*
 NOTE: Commenting out the destructor of the stream_wrapper will allow this function to compile.
 */
static future<int> will_make_compiler_fail() noexcept {
    stream_wrapper stream;
    async_device_resource resource{stream.get_stream()};
    co_return int{};
}
