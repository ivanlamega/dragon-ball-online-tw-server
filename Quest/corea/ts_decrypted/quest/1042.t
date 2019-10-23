CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1042;
	title = 104202;

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
				conv = 104209;
				ctype = 1;
				idx = 8031201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 104208;
				gtype = 1;
				area = 104201;
				goal = 104204;
				grade = 132203;
				rwd = 100;
				sort = 104205;
				stype = 2;
				taid = 1;
				title = 104202;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 104207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 8031201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 47;
				minlvl = 39;
			}
			CDboTSCheckClrQst
			{
				and = "1041;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 104214;
			nextlnk = 254;
			rwdtbl = 104201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8031401;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 104208;
			gtype = 1;
			oklnk = 2;
			area = 104201;
			goal = 104204;
			sort = 104205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 104202;
		}
	}
}

