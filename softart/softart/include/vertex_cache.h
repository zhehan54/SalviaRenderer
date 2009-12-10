#ifndef SOFTART_VERTEX_CACHE_H
#define SOFTART_VERTEX_CACHE_H

#include "decl.h"

#include <vector>
#include <utility>

#include "render_stage.h"

#include <boost/pool/pool.hpp>

class stream_assembler;

//������ֱ��������input vertexʱ����ֻ��low��������ã��������Ϊ���к�Ķ��㣬��hi idҲ��������
typedef size_t cache_entry_index;

class vertex_cache : public render_stage
{
public:
	virtual void set_vert_range(size_t minvert, size_t maxvert) = 0;
	virtual void reset() = 0;
	virtual void resize(size_t s) = 0;

	virtual vs_output& fetch(cache_entry_index id) = 0;
	virtual vs_output& fetch_for_write(cache_entry_index id) = 0;

	virtual vs_output* new_vertex() = 0;
	virtual void delete_vertex(vs_output* const pvert) = 0;
};

class default_vertex_cache : public vertex_cache
{
public:
	default_vertex_cache();

	void initialize(renderer_impl* psr);

	void set_vert_range(size_t minvert, size_t maxvert);
	void reset();
	void resize(size_t s);

	vs_output& fetch(cache_entry_index id);
	vs_output& fetch_for_write(cache_entry_index id);

	vs_output* new_vertex();
	void delete_vertex(vs_output* const pvert);

private:
	size_t vert_base_;
	vertex_shader* pvs_;
	stream_assembler* psa_;

	std::vector<bool> btransformed_;
	std::vector<vs_output> verts_;

	boost::pool<> verts_pool_;
	const viewport* pvp_;
};

#endif