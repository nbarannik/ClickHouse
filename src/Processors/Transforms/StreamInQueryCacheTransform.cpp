#include <Processors/Transforms/StreamInQueryCacheTransform.h>

namespace DB
{

StreamInQueryCacheTransform::StreamInQueryCacheTransform(
    const Block & header_,
    std::shared_ptr<QueryCache::Writer> query_cache_writer_,
    QueryCache::Writer::ChunkType chunk_type_)
    : ISimpleTransform(header_, header_, false)
    , query_cache_writer(query_cache_writer_)
    , chunk_type(chunk_type_)
{
    LOG_TRACE(getLogger("QueryCache"),
                        "Build stream in query cache {}", chunk_type_);
}

void StreamInQueryCacheTransform::transform(Chunk & chunk)
{
    LOG_TRACE(getLogger("QueryCache"),
                        "Transform stream in query cache");
                        
    query_cache_writer->buffer(chunk.clone(), chunk_type);
}

void StreamInQueryCacheTransform::finalizeWriteInQueryCache()
{
    if (!isCancelled())
        query_cache_writer->finalizeWrite();
}

};
