CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1429;
	title = 142902;

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
				conv = 142909;
				ctype = 1;
				idx = 4071108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 142908;
				gtype = 0;
				area = 142901;
				goal = 142904;
				grade = 132203;
				rwd = 100;
				sort = 142905;
				stype = 2;
				taid = 1;
				title = 142902;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 142907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4071108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
			CDboTSCheckClrQst
			{
				and = "1407;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
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
			cont = 142908;
			gtype = 0;
			oklnk = 2;
			area = 142901;
			goal = 142904;
			sort = 142905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 142902;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 142914;
			nextlnk = 254;
			rwdtbl = 142901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5531101;
			}
		}
	}
}

