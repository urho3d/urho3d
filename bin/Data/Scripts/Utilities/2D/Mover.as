// Mover script object class
//    - handles entity (enemy, platform...) translation along a path (set of Vector2 points)
//    - supports looping paths and animation flip
//    - default speed is 0.8 if 'Speed' property is not set in the tmx file objects

class Mover : ScriptObject
{
    float speed = 0.8f;
    Array<Vector2> path;
    int currentPathID = 1;
    float emitTime = 0.0f;
    float fightTimer = 0.0f;
    float flip = 0.0f;
    uint bufferSize = 0;

    void Load(Deserializer& deserializer)
    {
        bufferSize = deserializer.ReadUInt(); // Get buffer size
        SetPathAttr(deserializer.ReadVectorBuffer(bufferSize));
    }

    void Save(Serializer& serializer)
    {
        serializer.WriteVectorBuffer(GetPathAttr(serializer));
    }

    void SetPathAttr(VectorBuffer buffer)
    {
        if (buffer.size == 0)
            return;

        while (!buffer.eof)
            path.Push(buffer.ReadVector2());
    }

    VectorBuffer GetPathAttr(Serializer& serializer)
    {
        VectorBuffer buffer = VectorBuffer();

        for (uint i=0; i < path.length; ++i)
            buffer.WriteVector2(path[i]);

        bufferSize = buffer.size;
        serializer.WriteUInt(bufferSize);

        return buffer;
    }

    void Update(float timeStep)
    {
        if (path.length < 2)
            return;

        // Handle Orc states (idle/wounded/fighting)
        if (node.name == "Orc")
        {
            AnimatedSprite2D@ animatedSprite = node.GetComponent("AnimatedSprite2D");
            String anim = "run";

            // Handle wounded state
            if (emitTime > 0.0f)
            {
                emitTime += timeStep;
                anim = "dead";

                // Handle dead
                if (emitTime >= 3.0f)
                {
                    node.Remove();
                    return;
                }
            }
            else
            {
                // Handle fighting state
                if (fightTimer > 0.0f)
                {
                    anim = "attack";
                    flip = character2DNode.position.x - node.position.x;
                    fightTimer += timeStep;
                    if (fightTimer >= 3.0f)
                        fightTimer = 0.0f; // Reset
                }
                // Flip Orc animation according to speed, or player position when fighting
                animatedSprite.flipX = flip >= 0.0f;
            }
            // Animate
            if (animatedSprite.animation != anim)
                animatedSprite.SetAnimation(anim);
        }

        // Don't move if fighting or wounded
        if (fightTimer > 0.0f || emitTime > 0.0f)
            return;

        // Set direction and move to target
        Vector2 dir = path[currentPathID] - node.position2D;
        Vector2 dirNormal = dir.Normalized();
        node.Translate(Vector3(dirNormal.x, dirNormal.y, 0.0f) * Abs(speed) * timeStep);
        flip = dir.x;

        // Check for new target to reach
        if (Abs(dir.length) < 0.1f)
        {
            if (speed > 0.0f)
            {
                if (currentPathID + 1 < path.length)
                    currentPathID = currentPathID + 1;
                else
                {
                    // If loop, go to first waypoint, which equates to last one (and never reverse)
                    if (path[currentPathID] == path[0])
                    {
                        currentPathID = 1;
                        return;
                    }
                    // Reverse path if not looping
                    currentPathID = currentPathID - 1;
                    speed = -speed;
                }
            }
            else
            {
                if (currentPathID - 1 >= 0)
                    currentPathID = currentPathID - 1;
                else
                {
                    currentPathID = 1;
                    speed = -speed;
                }
            }
        }
    }
}