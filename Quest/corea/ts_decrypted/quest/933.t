CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 933;
	title = 93302;

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
				conv = 93309;
				ctype = 1;
				idx = 2951304;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 93308;
				gtype = 1;
				area = 93301;
				goal = 93304;
				grade = 132203;
				rwd = 100;
				sort = 93305;
				stype = 2;
				taid = 1;
				title = 93302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 93307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2951304;
			}
			CDboTSCheckLvl
			{
				maxlvl = 41;
				minlvl = 33;
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
			cont = 93308;
			gtype = 1;
			oklnk = 2;
			area = 93301;
			goal = 93304;
			sort = 93305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 93302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 93314;
			nextlnk = 254;
			rwdtbl = 93301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3144105;
			}
		}
	}
}

