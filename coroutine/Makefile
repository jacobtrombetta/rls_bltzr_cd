CUDA_ROOT_DIR=/usr/local/cuda-12.1
CUDA_LIB_DIR= -L$(CUDA_ROOT_DIR)/lib64
CUDA_INC_DIR= -I$(CUDA_ROOT_DIR)/include
CUDA_LINK_LIBS= -lcudart

coroutine_nvcc : kernel.o
	g++ -std=c++20 kernel.o -o $@ $(CUDA_INC_DIR) $(CUDA_LIB_DIR) $(CUDA_LINK_LIBS)

kernel.o : kernel.cu
	nvcc -std=c++20 -c $< -o $@ 

clean:
	rm -f kernel.o