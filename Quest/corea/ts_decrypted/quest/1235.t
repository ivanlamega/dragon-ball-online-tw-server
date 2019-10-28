CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1235;
	title = 123502;

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
				conv = 123509;
				ctype = 1;
				idx = 1111114;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 123508;
				gtype = 1;
				area = 123501;
				goal = 123504;
				grade = 132203;
				rwd = 100;
				sort = 123505;
				stype = 1;
				taid = 1;
				title = 123502;
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
			cont = 123508;
			gtype = 1;
			oklnk = 2;
			area = 123501;
			goal = 123504;
			sort = 123505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 123502;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 123514;
			nextlnk = 254;
			rwdtbl = 123501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372101;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 123507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1111114;
			}
			CDboTSCheckLvl
			{
				maxlvl = 51;
				minlvl = 43;
			}
		}
	}
}

