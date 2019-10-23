CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1364;
	title = 136402;

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
				conv = 136409;
				ctype = 1;
				idx = 4372206;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 136408;
				gtype = 1;
				area = 136401;
				goal = 136404;
				grade = 132203;
				rwd = 100;
				sort = 136405;
				stype = 2;
				taid = 1;
				title = 136402;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 136407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4372206;
			}
			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
			}
			CDboTSCheckClrQst
			{
				and = "1363;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 136408;
			gtype = 1;
			oklnk = 2;
			area = 136401;
			goal = 136404;
			sort = 136405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 136402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 136414;
			nextlnk = 254;
			rwdtbl = 136401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1654103;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

