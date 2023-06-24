#pragma once

class IndexBuffer {
public:
    /**
     * @brief IndexBuffer constructor
     * @param data pointer to the data
     * @param count number of indices
     */
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    /**
	 * @brief bind the index buffer
	 */
    void bind() const;
    /**
    * @brief unbind the index buffer
    */
    void unbind() const;

    /**
	 * @brief get the number of indices
	 * @return number of indices
	 */
    inline unsigned int getCount() const
    { 
        return count_;
    }

private:
    unsigned int indexBufferID_;
    unsigned int count_;
};
