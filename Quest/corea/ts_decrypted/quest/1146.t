CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1146;
	title = 114602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 114609;
				ctype = 1;
				idx = 1551101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 114608;
				gtype = 1;
				area = 114601;
				goal = 114604;
				grade = 132203;
				rwd = 100;
				sort = 114605;
				stype = 1;
				taid = 1;
				title = 114602;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 114608;
			gtype = 1;
			oklnk = 2;
			area = 114601;
			goal = 114604;
			sort = 114605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 114602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 114614;
			nextlnk = 254;
			rwdtbl = 114601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 114607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1551101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
			CDboTSCheckClrQst
			{
				and = "1145;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

