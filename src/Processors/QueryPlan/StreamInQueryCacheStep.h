#pragma once
#include <memory>
#include <Processors/QueryPlan/ITransformingStep.h>
#include <Processors/Transforms/StreamInQueryCacheTransform.h>
#include "Interpreters/Cache/QueryCache.h"

namespace DB
{

class StreamInQueryCacheStep : public ITransformingStep
{
public:
    StreamInQueryCacheStep(
        const Header & input_header_,
        std::shared_ptr<QueryCache::Writer> writer_
    );

    String getName() const override { return "StreamInQueryCacheStep"; }

    void transformPipeline(QueryPipelineBuilder & pipeline, const BuildQueryPipelineSettings &) override;

private:
    void updateOutputHeader() override
    {
        output_header = input_headers.front();
    }

    std::shared_ptr<QueryCache::Writer> writer;
};

}
