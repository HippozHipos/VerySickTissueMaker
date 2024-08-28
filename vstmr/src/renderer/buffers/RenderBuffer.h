namespace vstmr {

	class RenderBuffer
	{
	public:
		RenderBuffer();

	public:
		void Bind();
		static void UnBind();
		void MakeStorage(int widht, int height);
		void AttachToFrameBuffer();

	private:
		unsigned int m_buffer_id;
	};
}